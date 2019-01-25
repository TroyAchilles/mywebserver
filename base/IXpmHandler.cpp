#include "IXpmHandler.h"
#include "Debug.h"

IXpmHandler::IXpmHandler(std::fstream* fs)
    : ImageIOHandler(fs)
{

}

bool IXpmHandler::write(const Image* img)
{
    D_UNUSED(img);
    return false;
}
