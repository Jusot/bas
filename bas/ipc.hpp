#ifndef BAS_IPC_HPP
#define BAS_IPC_HPP

#include <string>
#include "message.hpp"

namespace bas
{
inline constexpr char UN_PRE[] = "/tmp/bas";
namespace ipc
{
Message sendto(int id, Message msg, bool read_or_not = true);
ssize_t sendto(int id, char* buf, size_t len);

}
}

#endif // BAS_IPC_HPP