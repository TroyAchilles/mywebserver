#ifndef IMAGEIOHANDLER_H
#define IMAGEIOHANDLER_H
#include "factory.h"
#include <string>
#include "Image.h"

class ImageIOHandler
{
    public:
        ImageIOHandler(std::fstream* fs);
        virtual bool write(const Image* img) = 0;
        virtual bool sync();
        int fd();
    public:
        std::fstream* 			_fs;
};

#define REGISTER_ImageIOHandler(T, key) static factory<ImageIOHandler, std::fstream*>::register_t<T> register_t_##T##_(key);
#define ImageIOHandlerFactory factory<ImageIOHandler, std::fstream*>::instance()

#endif // IMAGEIOHANDLER_H
