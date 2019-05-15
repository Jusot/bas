#include <string>
#include <iostream>
#include "loop.hpp"

using namespace std;
using namespace bas;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "bas [id]" << endl;
    }

    auto id = stoi(argv[1]);
    Loop loop(id);

    loop.run();

    return 0;
}