
#include <iostream>
#include <iomanip>
#include "dshfs.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>

#define NOMINMAX
#include <Windows.h>

using namespace dshfs;

void doStringTransform(std::iostream& strm)
{
    std::string s;

    std::getline(strm, s);
    for(auto& x : s)    x += 1;
    std::cout << ": " << s << '\n';
    //strm.flush();
    strm << s << '\n';
    //strm.flush();
}

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
        /*
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
        }*/
        
        /*
        std::string str;
        f.seekg(9);
        //f << "This is a test\n" << 168 << " - " << std::hex << (128+0xA) << std::endl;
        while(getline(f, str))
        {
            std::cout << str << '\n';
        }
        std::cout << ">>EOF<<" << std::endl;*/
        
        CopyFileA("tester.txt", "thistest.txt", FALSE);
        CopyFileA("tester.txt", "thistest_control.txt", FALSE);

        FileStream file("thistest.txt", FileMode::rw);
        std::fstream ctrl("thistest_control.txt", std::ios_base::in | std::ios_base::out);
        if(ctrl.good())
            std::cout << "This is good!\n";

        for(int i = 0; i < 2; ++i)
        {
            doStringTransform(file);
            //doStringTransform(ctrl);
        }
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}