#include <cassert>
#include <thread>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>

#include "message.hpp"
#include "loop.hpp"
#include "ipc.hpp"

using namespace std;
using namespace bas;

vector<int> ids =
{
    1, 2, 3, 4, 5, 6, 7, 8
};

Loop::Loop(int id)
  : id_(id),
    sockfd_(socket(AF_UNIX, SOCK_STREAM, 0)),
    leader_(-1)
{
    auto un_path = UN_PRE + to_string(id);
    addr_.sun_family = AF_UNIX;
    strcpy(addr_.sun_path, un_path.c_str());

    bind(sockfd_, (sockaddr *)&addr_, sizeof addr_);
}

void Loop::run()
{
    this_thread::sleep_for(10s);
    start_elect();
    while (true)
    {
        this_thread::sleep_for(3s);
        if (!check_leader_alive())
        {
            start_elect();
        }
    }
}

void Loop::start_elect()
{
    leader_ = -1;
    if (id_ == ids.back())
    {
        leader_ = id_;
        broadcast_victory();
    }
    else
    {
        bool get_reply = false;
        for (auto id : ids)
        {
            if (id > id_)
            {
                auto msg = ipc::sendto(id, { id_, ELECT });
                if (msg.id == id_)
                {
                    // no reply
                }
                else
                {
                    assert(msg.id > id_ && msg.type == ALIVE);
                    get_reply = true;
                    break;
                }
            }
        }
        if (!get_reply)
        {
            broadcast_victory();
        }
        else
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (leader_cond_.wait_for(lock, 3s, [&] () { return leader_ != -1;}))
            {
                // ok
            }
            else
            {
                // timeout
                start_elect();
            }
        }
    }
    
}

void Loop::recv()
{
    listen(sockfd_, 10);

    int client_sockfd;
    struct sockaddr_un client_addr;
    socklen_t len = sizeof client_addr;

    while (true)
    {
        Message msg;
        client_sockfd = accept(sockfd_, (sockaddr *)&client_addr, &len);
        auto n = read(client_sockfd, &msg, sizeof msg);
        if (n == 1)
        {
            write(client_sockfd, " ", 1);
        }
        else if (IS_VICTORY(msg.type))
        {
            leader_ = msg.id;
            leader_cond_.notify_all();
        }
        else if (IS_ELECT(msg.type) && msg.id < id_)
        {
            msg = { id_, ALIVE };
            write(client_sockfd, &msg, sizeof msg);
        }
    }
}

void Loop::start_recv()
{
    thread t([this]{
        this->recv();
    });
    t.detach();
}

void Loop::broadcast_victory() const
{
    for (auto id : ids)
    {
        if (id != id_)
        {
            ipc::sendto(id, { id_, VICTORY }, false);
        }
    }
}

bool Loop::check_leader_alive() const
{
    char buf = ' ';
    assert(leader_ != -1);
    return ipc::sendto(leader_, &buf, 1) != -1;
}
