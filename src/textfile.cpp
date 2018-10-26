
#include "textfile.h"

/*
    I hate Windows linebreaks.

    This class is sort of a wrapper to convert linebreaks (to read a file as text mode).
    This is because WinAPI and other file sources (like reading from a zip or whatever) may
    not have a native text mode, and so we need to simulate it here.

    This class will convert '\r' and '\r\n' to '\n' from all reads.  If is accomplished as follows:
        - When you see \r, replace with \n
        - When you see \n, drop it if the previous character was \r

    I do not do anything for writes, because there is no conceivable reason to ever use any other
    kind of linebreak apart from \n unless you are testing code which converts things to \n.

    And I absolutely loathe that in 2018, when all languages, editors, tools, APIs, etc all have
    unanimously decided that \n is the standard line break, and they ALL support \n line breaks...
    we STILL have to deal with this text mode conversion bullshit.
*/

namespace dshfs
{
    TextFile::TextFile(File::Ptr&& src) 
        : srcFile( std::move(src) )
        , lastCharWasCR(false)
    {}

    TextFile::~TextFile()
    {}
    
    void        TextFile::close()                               { srcFile->close();                 }
    bool        TextFile::isOpen() const                        { return srcFile->isOpen();         }
    bool        TextFile::isReadable() const                    { return srcFile->isReadable();     }
    bool        TextFile::isWritable() const                    { return srcFile->isWritable();     }
    File::pos_t TextFile::tell() const                          { return srcFile->tell();           }
    File::pos_t TextFile::seek(pos_t pos, Origin origin)
    {
        lastCharWasCR = false;
        return srcFile->seek(pos,origin);
    }

    File::pos_t TextFile::write(const void* buf, pos_t size)
    {
        if( srcFile->isWritable() && size > 0 )
        {
            lastCharWasCR = false;
            return srcFile->write(buf,size);
        }
        return 0;
    }
    
    File::pos_t TextFile::read(void* buf, pos_t size)
    {
        char* dst = reinterpret_cast<char*>(buf);
        pos_t total = 0;

        while(size > 0)
        {
            auto block = srcFile->read(dst,size);
            if(block <= 0)          break;

            block = convertBlock(dst, block);
            total += block;
            dst += block;
            size -= block;
        }
        return total;
    }

    File::pos_t TextFile::convertBlock(char* ptr, pos_t size)
    {
        pos_t dst = 0;
        pos_t src = 0;

        while(src < size)
        {
            char c = ptr[src++];
            switch(c) {
            case '\r':
                lastCharWasCR = true;
                ptr[dst++] = '\n';
                break;

            case '\n':
                if(!lastCharWasCR)
                {
                    ptr[dst++] = '\n';
                }
                lastCharWasCR = false;
                break;

            default:
                ptr[dst++] = c;
                lastCharWasCR = false;
                break;
            }
        }
        return dst;
    }
}