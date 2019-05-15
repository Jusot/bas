#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "ipc.hpp"

using namespace std;

namespace bas::ipc
{
Message sendto(int id, Message msg, bool read_or_not)
{
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    auto un_path = UN_PRE + to_string(id);
    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, un_path.c_str());
    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1) return msg;
    if (write(sockfd, &msg, sizeof msg) == -1) return msg;
    if (read_or_not) read(sockfd, &msg, sizeof msg);
    return msg;
}
}