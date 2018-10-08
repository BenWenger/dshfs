
#include <iostream>
#include "dshfs.h"

using namespace dshfs;

int main()
{
    try
    {
        auto file = fs.openFile("test.txt");
        char utf8name[40];
        auto len = file->read(utf8name, 39);
        utf8name[len] = '\0';


        file = fs.openFile(utf8name);
        char dat[100];
        len = file->read(dat, 99);
        dat[len] = '\0';

        std::cout << "Success:  " << dat;
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}