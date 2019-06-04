#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include "message.hpp"

namespace bas
{
enum SendOrRecv
{
    SEND,
    RECV
};

void log(SendOrRecv sr, int id, int type);
void log(const char* str);
void log(const std::string& str);
}

#endif // LOG_HPP