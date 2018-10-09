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

            Text =              (1<<7),

            rb =                Read | ShareRead,
            rwb =               Read | Write | Create,
            wb =                Read | Write | Create | Truncate,
            
            rt =                rb  | Text,
            rwt =               rwb | Text,
            wt =                wb  | Text
        };
    }
}


#endif