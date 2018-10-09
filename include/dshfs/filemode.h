#ifndef DSHFS_FILEMODE_H_INCLUDED
#define DSHFS_FILEMODE_H_INCLUDED

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
}


#endif