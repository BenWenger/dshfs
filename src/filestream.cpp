
#include "dshfs/filestream.h"

namespace dshfs
{

    FileStream::FileStream(const std::string& path, int mode, bool convertLineBreaks)
        : std::iostream( buffer = new FileBuf(path,mode,convertLineBreaks) )
    {}

    FileStream::~FileStream()
    {
        delete buffer;
    }

}