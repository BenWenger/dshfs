
#include "dshfs/filestream.h"

namespace dshfs
{

    FileStream::FileStream(const std::string& path, int mode)
        : std::iostream( buffer = new FileBuf(path,mode) )
    {}

    FileStream::~FileStream()
    {
        delete buffer;
    }

}