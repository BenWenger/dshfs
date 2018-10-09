#ifdef _WIN32
#include "windows_diskfilesystem.h"
#include "windows_diskfile.h"
#include "dshfs/error.h"
#include "../textfile.h"

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
    
    bool Windows_DiskFileSystem::isFilenameAbsolute(const std::string& filename) const
    {
        if(filename.length() < 2)   return false;
        return filename[1] == ':';
    }
}

#endif