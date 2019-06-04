#include "log.hpp"

#include <cassert>
#include <iostream>

namespace bas
{
void log(SendOrRecv sr, int id, int type)
{
    if (sr == SEND)
        std::cout << "send\t";
    std::cout << "id: " << id << " type: ";
    switch (type)
    {
    case ELECT:
        std::cout << "ELECT" << std::endl;
        break;
    
    case ALIVE:
        std::cout << "ALIVE" << std::endl;
        break;

    case VICTORY:
        std::cout << "VICTORY" << std::endl;
        break;

    default:
        std::cout << "UNKNOWN TYPE" << std::endl;
        assert(0);
    }
}

void log(const char* str)
{
    std::cout << str << std::endl;
}

void log(const std::string& str)
{
    std::cout << str << std::endl;
}

} // namespace bas