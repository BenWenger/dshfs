#ifndef DSHFS_FILE_H_INCLUDED
#define DSHFS_FILE_H_INCLUDED

#include <string>
#include <stdint.h>

namespace dshfs
{
    namespace FileMode
    {
        enum
        {
            Read =              (1<<0),
            Write =             (1<<1),
            Create =            (1<<2),
            Truncate =          (1<<3),
            FailIfExists =      (1<<4),

            ShareRead =         (1<<5),
            ShareWrite =        (1<<6),

            r =                 Read | ShareRead,
            rw =                Read | Write | Create,
            w =                 Read | Write | Create | Truncate
        };
    }

    class File
    {
    public:
        typedef std::int64_t            pos_t;
        enum class Origin               { Set, Cur, End };

        DLL File();
        DLL File(const std::string& path, int flags = FileMode::r);
        DLL File(const File& rhs)           = delete;
        DLL File(File&& rhs);

        DLL File& operator = (const File&)  = delete;
        DLL File& operator = (File&& rhs);

        DLL ErrorCode   open(const std::string& path, int flags = FileMode::r);
        DLL void        close();
        DLL bool        isOpen() const;

        DLL pos_t       read(void* buf, pos_t size);
        DLL pos_t       write(const void* buf, pos_t size);

        DLL pos_t       seek(pos_t pos, Origin origin = Origin::Set);
        DLL pos_t       tell();

    private:
        void*           rawdat;
    };
}


#endif