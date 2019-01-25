#ifndef IXPMHANDLER_H
#define IXPMHANDLER_H
#include "ImageIOhandler.h"

class IXpmHandler : public ImageIOHandler
{
    public:
        IXpmHandler(std::fstream* fs);
        bool write(const Image* img);
};
REGISTER_ImageIOHandler(IXpmHandler, "xpm")
#endif // IXPMHANDLER_H
