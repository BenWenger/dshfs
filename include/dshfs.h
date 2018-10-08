#ifndef DSHFS_H_INCLUDED
#define DSHFS_H_INCLUDED

#include "dshfs/exportdefine.h"
#include "dshfs/error.h"
#include "dshfs/filename.h"
#include "dshfs/file.h"
#include "dshfs/filesystem.h"


#ifdef _MSC_VER
    #ifndef DSHFS_LIBRARY_BUILD
        #ifdef _DEBUG
            #pragma comment(lib, "dshfs_d.lib")
        #else
            #pragma comment(lib, "dshfs.lib")
        #endif
    #endif
#endif

#endif