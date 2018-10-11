
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

std::string readFullTextFile(const std::string& filename)
{
    char buffer[1024];
    auto file = fs.openFile(filename, FileMode::rt);
    auto siz = file->read(buffer, 1023);
    buffer[siz] = 0;

    return std::string(buffer);
}

int main()
{
    srand( (unsigned)time(nullptr) );
    try
    {
        std::string fn;
        auto i = fs.iterateDir("C:/Users/benwe/Desktop/C++/Projects/dshfs/");
        while(i)
        {
            fn = i->fileName;
            std::cout << fn;
            if(i->isDir())
                std::cout << '/';
            std::cout << '\n';
            ++i;
        }
        /*
        FileStream f(fn,FileMode::rt);
        std::string s;
        while(std::getline(f, s))
        {
            std::cout << s << std::endl;
        }*/
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}