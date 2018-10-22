#ifndef DSHFS_FILE_H_INCLUDED
#define DSHFS_FILE_H_INCLUDED

#include <string>
#include <cstdint>
#include <memory>
#include "exportdefine.h"
#include "filemode.h"

namespace dshfs
{
    class File
    {
    public:
        typedef std::unique_ptr<File>   Ptr;
        typedef std::int64_t            pos_t;
        enum class Origin               { Set, Cur, End };

        DSHFS_API virtual ~File()     {}
        DSHFS_API virtual void        close() = 0;
        DSHFS_API virtual bool        isOpen() const = 0;
        DSHFS_API virtual bool        isReadable() const = 0;
        DSHFS_API virtual bool        isWritable() const = 0;
        DSHFS_API virtual pos_t       read(void* buf, pos_t size) = 0;
        DSHFS_API virtual pos_t       write(const void* buf, pos_t size) = 0;
        
        DSHFS_API virtual pos_t       seek(pos_t pos, Origin origin = Origin::Set) = 0;
        DSHFS_API virtual pos_t       tell() const = 0;

    protected:
        File() = default;

    private:
        // no copying/moving
        File(const File&) = delete;
        File& operator = (const File&) = delete;
        File(File&&) = delete;
        File& operator = (File&&) = delete;
    };
}


#endif