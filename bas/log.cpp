#include "log.hpp"

#include <iostream>
#include <cassert>
#include <sstream>
#include <unistd.h>

namespace bas
{
void log(SendOrRecv sr, int id, int type)
{
    std::ostringstream sout;
    if (sr == SEND)
        sout << "send\t";
    else
        sout << "recv\t";
    sout << "id: " << id << " type: ";
    switch (type)
    {
    case ELECT:
        sout << "ELECT" << std::endl;
        break;
    
    case ALIVE:
        sout << "ALIVE" << std::endl;
        break;

    case VICTORY:
        sout << "VICTORY" << std::endl;
        break;

    default:
        sout << "UNKNOWN TYPE" << std::endl;
        assert(0);
    }
    ::write(STDOUT_FILENO, sout.str().c_str(), sout.str().size());
}

void log(const char* str)
{
    std::ostringstream sout;
    sout << str << std::endl;
    ::write(STDOUT_FILENO, sout.str().c_str(), sout.str().size());
}

void log(const std::string& str)
{
    std::ostringstream sout;
    sout << str << std::endl;
    ::write(STDOUT_FILENO, sout.str().c_str(), sout.str().size());
}

} // namespace bas