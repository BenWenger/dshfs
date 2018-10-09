#ifndef DSHFS_TEXTFILE_H_INCLUDED
#define DSHFS_TEXTFILE_H_INCLUDED

#include "dshfs/file.h"

namespace dshfs
{
    class TextFile : public File
    {
    public:
                TextFile(File::Ptr&& src);
        virtual ~TextFile();
        virtual void                close() override;
        virtual bool                isOpen() const override;
        virtual bool                isReadable() const override;
        virtual bool                isWritable() const override;
        virtual pos_t               read(void* buf, pos_t size) override;
        virtual pos_t               write(const void* buf, pos_t size) override;
        
        virtual pos_t               seek(pos_t pos, Origin origin = Origin::Set) override;
        virtual pos_t               tell() const override;

    private:
        File::Ptr                   srcFile;
        bool                        lastCharWasCR;

        pos_t                       convertBlock(char* ptr, pos_t size);
    };
}


#endif