
#include <iostream>
#include <iomanip>
#include "dshfs.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace dshfs;

int main()
{
    srand( (unsigned)time(nullptr) );
    try
    {/*
        auto file = fs.openFile("test.txt");
        char utf8name[40];
        auto len = file->read(utf8name, 39);
        utf8name[len] = '\0';


        file = fs.openFile(utf8name);
        char dat[100];
        len = file->read(dat, 99);
        dat[len] = '\0';

        std::cout << "Success:  " << dat;*/

        std::string things[4];
        int pages[4] = {0,1,2,3};
        std::random_shuffle(pages, pages+4);
        int tells[4];
        
        FileStream f("tester.txt", FileMode::rt);

        for(int page : pages)
        {
            f.seekg(page * 8);
            getline(f, things[page]);
            tells[page] = static_cast<int>(f.tellg());
        }

        for(int i = 0; i < 4; ++i)
        {
            std::cout << things[i] << "   " << tells[i] << std::endl;
        }
        
        /*
        std::string str;
        f.seekg(9);
        //f << "This is a test\n" << 168 << " - " << std::hex << (128+0xA) << std::endl;
        while(getline(f, str))
        {
            std::cout << str << '\n';
        }
        std::cout << ">>EOF<<" << std::endl;*/
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}