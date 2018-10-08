#ifndef DSHFS_WINDOWS_DISKFILE_H_INCLUDED
#define DSHFS_WINDOWS_DISKFILE_H_INCLUDED
#ifdef _WIN32

#include "dshfs/file.h"
#include "winheader.h"

namespace dshfs
{
    class Windows_DiskFile : public File
    {
    public:
                Windows_DiskFile();
        virtual ~Windows_DiskFile() { close(); }
        virtual void                close() override;
        virtual bool                isOpen() const override;
        virtual pos_t               read(void* buf, pos_t size) override;
        virtual pos_t               write(const void* buf, pos_t size) override;
        
        virtual pos_t               seek(pos_t pos, Origin origin = Origin::Set) override;
        virtual pos_t               tell() const override;

    private:
        friend class                Windows_DiskFileSystem;
        static File::Ptr            open(const std::string& path, int flags);

        HANDLE                      handle;
    };
}


#endif
#endif