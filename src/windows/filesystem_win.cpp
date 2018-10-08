
#include "winheader.h"
#include "dshfs.h"


namespace dshfs
{
    namespace
    {
        struct Impl
        {
            std::string     curDirectory;

            void populateCurrentDirectory()
            {
                auto len = GetCurrentDirectoryW(0,nullptr);
                std::wstring path(len, L'\0');
                len = GetCurrentDirectoryW( len, &path[0] );        // cheesing std::string a bit
                path.resize(len);

                path.push_back('/');

                curDirectory = fromWindowsName(path);
            }
        };
        #define impl        reinterpret_cast<Impl*>(rawdat)
    }


    FileSystem::FileSystem()
    {
        rawdat = reinterpret_cast<Impl*>(new Impl);
        impl->populateCurrentDirectory();
    }

    FileSystem::~FileSystem()
    {
        delete impl;
    }

    std::string FileSystem::getCurrentDirectory() const
    {
        return impl->curDirectory;
    }



}
