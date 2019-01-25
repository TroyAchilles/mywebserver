#include "ImageIOhandler.h"
#include <unistd.h>
#include <fstream>
#include "Debug.h"

ImageIOHandler::ImageIOHandler(std::fstream* fs)
    : _fs(fs)
{

}


int ImageIOHandler::fd()
{
    struct Helper : public std::filebuf
    {
        int handle() { return _M_file.fd();}
    };

    return static_cast<Helper*>(_fs->rdbuf())->handle();
}

bool ImageIOHandler::sync()
{
    PD(fsync(fd()));
    return 0 == fsync(fd());
}
