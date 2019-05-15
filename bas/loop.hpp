#ifndef BAS_LOOP_HPP
#define BAS_LOOP_HPP

#include <sys/un.h>

namespace bas
{
class IPC;

class Loop
{
  public:
    Loop(int id);
    void run();
    void start_recv();

  private:
    void recv();

    int id_;
    int sockfd_;
    sockaddr_un addr_;
    int leader_;
};
}

#endif // BAS_LOOP_HPP