#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "log.hpp"
#include "ipc.hpp"

using namespace std;

namespace bas
{

Message ipc::sendto(int id, Message msg, bool read_or_not)
{
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1)
        return msg;
    auto un_path = UN_PRE + to_string(id);
    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, un_path.c_str());
    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
        goto end;
    if (write(sockfd, &msg, sizeof msg) == -1)
        goto end;
    log(SEND, id, msg.type);
    if (read_or_not)
    {
        if (read(sockfd, &msg, sizeof msg) != -1)
            log(RECV, msg.id, msg.type);
        else
            goto end;
    }

    end:
        close(sockfd);
        return msg;
}

ssize_t ipc::sendto(int id, char* buf, size_t len)
{
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1)
        return -1;
    auto un_path = UN_PRE + to_string(id);
    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, un_path.c_str());
    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
        return -1;
    if (write(sockfd, buf, len) == -1)
        return -1;
    return read(sockfd, buf, len);
}

}