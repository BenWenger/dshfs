#ifndef DSHFS_EXPORTDEFINE_H_INCLUDED
#define DSHFS_EXPORTDEFINE_H_INCLUDED


//  NOTE for the library build, 'DSHFS_LIBRARY_BUILD' should be defined.

#ifdef DSHFS_LIBRARY_BUILD
    #ifdef _WIN32
        #define DSHFS_API   __declspec(dllexport)
    #else
        #define DSHFS_API
    #endif
#else
    #ifdef _WIN32
        #define DSHFS_API   __declspec(dllimport)
    #else
        #define DSHFS_API
    #endif
#endif


#endif