
#include <iostream>
#include "dshfs.h"

using namespace dshfs;

int main()
{
    File f;
    auto res = f.open("testtest.txt");
    if(f.isOpen())
        std::cout << "File opened OK!\n";
    else
        std::cout << "ERROR\n";

    char buffer[15];
    f.read(buffer, 14);
    buffer[14] = 0;
    std::cout << "file contents:  " << buffer << '\n';

    char c;
    c = std::cin.get();
}