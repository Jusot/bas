#ifndef BAS_IPC_HPP
#define BAS_IPC_HPP

#include <string>
#include "message.hpp"

namespace bas
{
inline std::string UN_PRE = "/tmp/bas";
namespace ipc
{
Message sendto(int id, Message msg, bool read_or_not = true);
}
}

#endif // BAS_IPC_HPP