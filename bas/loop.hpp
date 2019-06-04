#ifndef BAS_LOOP_HPP
#define BAS_LOOP_HPP

#include <sys/un.h>
#include <cstdint>
#include <condition_variable>

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
    void start_elect();
    void broadcast_victory() const;
    bool check_leader_alive() const;

    std::condition_variable leader_cond_;
    std::mutex mutex_;

    int16_t id_;
    int sockfd_;
    sockaddr_un addr_;
    int16_t leader_;
};
}

#endif // BAS_LOOP_HPP