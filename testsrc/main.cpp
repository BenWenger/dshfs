
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
    fs.getExecutablePath();
    srand( (unsigned)time(nullptr) );
    try
    {
        const char* filename = "E:/Projects/bodobon/bodoasm/lua/6502.lua";

        std::string s;
        FileStream strm(filename);
        //std::ifstream strm(filename);
        while(true)
        {
            s.clear();
            s.resize(1025, '\0');
            strm.read(&s[0], 1024);
            s.resize( static_cast<size_t>(strm.gcount()) );
            std::cout << s.c_str();

            if(strm.gcount() <= 0)
                break;
        };

        std::cout << "\n\n\ndone\n";

        /*
        Filename dots;
        dots.setFullPath("C:/This/./has/../../some/dots/../confuse.txt/./wat/example.txt");
        dots.fullResolve();

        std::cout << dots.getFullPath() << std::endl;

        FileStream fs("../README.md");
        std::string s;
        while(getline(fs,s))
            std::cout << s << '\n';*/
    }
    catch(Error& e)
    {
        std::cout << "ERROR!!   " << e.what() << std::endl;
    }

    char c;
    c = std::cin.get();
}