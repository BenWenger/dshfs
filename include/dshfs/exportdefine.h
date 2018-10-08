#ifndef DSHFS_EXPORTDEFINE_H_INCLUDED
#define DSHFS_EXPORTDEFINE_H_INCLUDED


//  NOTE for the library build, 'DSHFS_LIBRARY_BUILD' should be defined.

#ifdef DSHFS_LIBRARY_BUILD
    #ifdef _WIN32
        #define DLL     __declspec(dllexport)
    #else
        #define DLL
    #endif
#else
    #ifdef _WIN32
        #define DLL     __declspec(dllimport)
    #else
        #define DLL
    #endif
#endif


#endif