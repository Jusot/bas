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
    while (true)
    {
        if (id_ == ids.back())
        {
            for (auto id : ids)
            {
                if (id != id_)
                {
                    ipc::sendto(id, { id_, VICTORY }, false);
                }
            }
        }
        else
        {
            for (auto id : ids)
            {
                if (id != id_)
                {
                    auto msg = ipc::sendto(id, { id_, ELECT });
                
                }
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
        read(client_sockfd, &msg, sizeof msg);
        if (IS_VICTORY(msg.type))
        {
            leader_ = msg.id;
        }
        else if (IS_ALIVE(msg.type) && msg.id > id_)
        {
            // wait for victory
            // if come, leader_ = msg.id
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