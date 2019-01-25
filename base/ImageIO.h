#pragma once
#include "Image.h"
#include "factory.h"

class ImageIOHandler;
class ImageIO
{
    public:
        ImageIO(string filename, string format);
        ImageIO(fstream* fs, string format);
        virtual ~ImageIO();

        bool canWrite();
        bool write(const Image* img);
        bool sync();

    private:
        string  							_format;
        std::shared_ptr<ImageIOHandler>	 	_ioHandler;
        fstream*							_filestream;
};
