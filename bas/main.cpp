#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "bas [id] [port]" << endl;
    }

    auto id   = stoi(argv[1]),
         port = argc < 3 ? 5000 : stoi(argv[2]);

    return 0;
}