#include "ImageIO.h"
#include "Debug.h"
#include "ImageIOhandler.h"
#include <fstream>

ImageIO::ImageIO(string filename, string format)
    : ImageIO(new fstream(filename, fstream::out), format)
{
}

ImageIO::ImageIO(fstream* fs, string format)
    : _format(format), _ioHandler(NULL), _filestream(fs)
{
}

ImageIO::~ImageIO()
{
    DELETE_PTR(_filestream);
}

bool ImageIO::canWrite()
{
    if (!_filestream->is_open())
    {
        PS("file can not open!");
        return false;
    }

    if (!_ioHandler &&
            !(_ioHandler = ImageIOHandlerFactory.produce(_format, _filestream)))
    {
        PS((string("create ImageIOHandler failed, unsupport format :") + _format).c_str());
        return false;
    }

    return true;
}

bool ImageIO::write(const Image* img)
{
    if (canWrite())
        return _ioHandler->write(img);
    return false;
}

bool ImageIO::sync()
{
    return canWrite() && _ioHandler->sync();
}
