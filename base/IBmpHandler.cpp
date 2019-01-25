#include "IBmpHandler.h"
#include "Debug.h"
#include <fstream>

IBmpHandler::IBmpHandler(std::fstream* fs)
    : ImageIOHandler(fs)
{
}

bool IBmpHandler::write(const Image *img)
{
    // build file header
    BMP_FILEHDR bf;
    bf.bfType = 0x4d42;
    bf.bfSize = sizeof(BMP_FILEHDR) + sizeof(BMP_INFOHDR) + (img->bpp() * img->w() * img->h());
    bf.bfReserved1 = 0;
    bf.bfReserved2 = 0;
    bf.bfOffBits = sizeof(BMP_FILEHDR) + sizeof(BMP_INFOHDR);

    // build info header
    BMP_INFOHDR bi;
    bi.biSize = sizeof(BMP_INFOHDR) - 4*4;
    bi.biWidth = img->w();
    bi.biHeight = img->h();
    bi.biPlanes = 1;
    bi.biBitCount = img->bpp() * 8;
    bi.biCompression = BI_BITFIELDS;
    bi.biSizeImage = img->bpp() * img->w() * img->h();
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    switch (img->format()) {
        case Image::Format_ARGB32:
            bi.biRedMask = 0x00FF0000;
            bi.biGreenMask = 0x0000FF00;
            bi.biBlueMask = 0x000000FF;
            bi.biAlphaMask = 0xFF000000;
            break;
        case Image::Format_RGB888:
            bi.biRedMask = 0x00FF0000;
            bi.biGreenMask = 0x0000FF00;
            bi.biBlueMask = 0x000000FF;
            bi.biAlphaMask = 0x00000000;
            break;
        case Image::Format_RGB16:
            bi.biRedMask = 0x0000F800;
            bi.biGreenMask = 0x000007E0;
            bi.biBlueMask = 0x0000001F;
            bi.biAlphaMask = 0x00000000;
            break;
        default:
            return false;  //不支持
    }

    //save to bmp file
    if (_fs->is_open() && _fs->good())
    {
        _fs->write(reinterpret_cast<char*>(&bf), sizeof(bf));
        _fs->write(reinterpret_cast<char*>(&bi), sizeof(bi));
        for(size_t i = img->h() - 1; i > 0; --i)
            _fs->write(img->data().get() + (img->w() * i * img->bpp()), img->w() * img->bpp());
        _fs->sync();
    }

    return _fs->good();
}
