#include <string>
#include <iostream>

#include <unistd.h>

#include "loop.hpp"
#include "log.hpp"

using namespace std;
using namespace bas;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "bas [id]" << endl;
    }
    log("pid=" + to_string(::getpid()));
    log(std::string("id=") + argv[1]);
    auto id = stoi(argv[1]);
    Loop loop(id);

    loop.run();

    return 0;
}