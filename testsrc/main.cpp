
#include <iostream>
#include "dshfs.h"

using namespace dshfs;

int main()
{
    try
    {
        auto file = fs.openFile("test.txt");
        if(file->isOpen())
            std::cout << "File opened OK!\n";
        else
            std::cout << "ERROR\n";

        char buffer[15];
        file->read(buffer, 14);
        buffer[14] = 0;
        std::cout << "file contents:  " << buffer << '\n';
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}