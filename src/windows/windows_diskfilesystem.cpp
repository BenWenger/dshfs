#ifdef _WIN32
#include "windows_diskfilesystem.h"
#include "windows_diskfile.h"
#include "dshfs/error.h"
#include "../textfile.h"
#include "windows_diriterator.h"

namespace dshfs
{
    FileSystem& fs = FileSystem::getInstance();


    FileSystem& FileSystem::getInstance()
    {
        static Windows_DiskFileSystem theFs;
        return theFs;
    }

    Windows_DiskFileSystem::Windows_DiskFileSystem()
    {
        auto len = GetCurrentDirectoryW(0,nullptr);
        std::wstring path(len, L'\0');
        len = GetCurrentDirectoryW( len, &path[0] );        // cheesing std::string a bit
        path.resize(len);

        path.push_back('/');

        curDirectory = winsupport::fromWindowsName(path);
    }

    std::string Windows_DiskFileSystem::getCurrentDirectory() const 
    {
        return curDirectory;
    }

    File::Ptr Windows_DiskFileSystem::openFile(const std::string& path, int mode)
    {
        File::Ptr file = Windows_DiskFile::open(path,mode);
        if(mode & FileMode::Text)
        {
            auto txtfile = std::make_unique<TextFile>( std::move(file) );
            file = std::move(txtfile);
        }
        return file;
    }
    
    bool Windows_DiskFileSystem::isAbsolute(const std::string& filename) const
    {
        if(filename.length() < 2)   return false;
        return filename[1] == ':';
    }

    DirIterator Windows_DiskFileSystem::iterateDir(const std::string& dir)
    {
        return DirIterator( std::make_unique<Windows_DirIterator>(dir) );
    }
    
    std::string Windows_DiskFileSystem::getExecutablePath() const
    {
        // GetModuleFileName sucks
        std::wstring            path(MAX_PATH,L'\0');
        std::size_t result;
        while(true)
        {
            result = static_cast<size_t>( GetModuleFileNameW(nullptr, &path[0], path.size()) );
            if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                path.resize(path.size() * 2);
            else
            {
                path.resize(result);
                break;
            }
        }

        return winsupport::fromWindowsName(path);
    }
}

#endif