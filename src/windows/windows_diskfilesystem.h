#ifndef DSHFS_WINDOWS_DISKFILESYSTEM_H_INCLUDED
#define DSHFS_WINDOWS_DISKFILESYSTEM_H_INCLUDED
#ifdef _WIN32

#include "dshfs/filesystem.h"
#include "winheader.h"

namespace dshfs
{
    class Windows_DiskFileSystem : public FileSystem
    {
    public:
        virtual                 ~Windows_DiskFileSystem() = default;

        virtual std::string     getCurrentDirectory() const override;

        virtual File::Ptr       openFile(const std::string& path, int mode = FileMode::rt) override;
        
        virtual bool            isAbsolute(const std::string& filename) const override;
        
        virtual DirIterator     iterateDir(const std::string& dir) override;
        
        virtual std::string     getExecutablePath() const override;

    private:
        friend class FileSystem;
        Windows_DiskFileSystem();
        std::string             curDirectory;
    };
}


#endif
#endif