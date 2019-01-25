/**
 * @file Image.cpp
 * @brief
 * @author dcl
 * @version 1.0.0.0
 * @date 2018-11-19
 */
#include "Image.h"
#include <string.h>
#include "Debug.h"
#include "ImageIO.h"
#include <iostream>
#include <algorithm>

Image::Image()
    : _w(0), _h(0), _format(Format_Invalid)
{

}

Image::Image(const char *p, size_t w, size_t h, Format format)
    : _w(w), _h(h), _format(format)
{
    _bpp = _format  == Format_Invalid ? 2 : (size_t)_format / 8;
    if (p)
    {
        _data = std::shared_ptr<char>(new char[_w * _h * _bpp], std::default_delete<char[]>());
        memmove(_data.get(), p, _w*_h*_bpp);
    }
}

Image::Image(const Image& img)
{
    *this = img;
}

//右值语义，浅拷贝
Image & Image::operator=(Image&& right)
{
    if (this != &right)
    {
        PS("浅拷贝");
        _w = right.w();
        _h = right.h();
        _bpp = right.bpp();
        _format = right.format();
        _data = right.data();
    }
    return *this;
}

//左值语义，深拷贝
Image & Image::operator=(const Image& right)
{
    if (this != &right)
    {
        PS("深拷贝");
        _w = right.w();
        _h = right.h();
        _bpp = right.bpp();
        _format = right.format();
        if (right.data())
        {
            _data = std::shared_ptr<char>(new char[right.w() * right.h() * right.bpp()], std::default_delete<char[]>());
            memmove(_data.get(), right.data().get(), _w * _h * _bpp);
        }
    }
    return *this;
}

/**
 * @brief Image::save Save the image to the file with the given \a filename, using
 *  	the given image file \a format. if \a format is empty, Image will attempt to guess the
 * 		format by looking at \a filename`s suffix.
 * @param filename  The image file named
 * @param format 	The image`s format, case in : "BMP","PNG","JPG",otherwise is "Invalid"
 * @return returns \c ture  if image was successfully saved; otherwise returns \c false
 */
bool Image::save(const string filename, const string format, bool bsync) const
{
    if (filename.empty() || !bool(_data) || _format == Format::Format_Invalid)
        return false;

    string assumedFormat = _surmiseFormat(filename, format);
    ImageIO writer(filename, assumedFormat);
    return writer.write(this) && bsync ? writer.sync() : 1;
}

/**
 * @brief Image::_surmiseFormat  Surmise the image format by using the given image file \a format.
 * 		If \a format is empty, will attempt to guess the format by looking at \a filename`s suffix.
 * @param filename  The image file named
 * @param format 	The image`s format, case in : "BMP","PNG","JPG",otherwise is "Invalid"
 * @return returns Returns a enmu of ImageFormat
 */
string Image::_surmiseFormat(const string& filename, const string& format) const
{
    string ret;
    if (!format.empty())
        ret = format;
    else if (!filename.empty())
        ret = filename.substr(filename.find_last_of('.') + 1);
    transform(ret.begin(), ret.end(), ret.begin(), ::tolower);

    return ret;
//    std::regex_match(format, regex("[Bb][Mm][Pp]$"));
//    std::regex_search(filename, regex("\\.[Bb][Mm][Pp]$"));
}

bool  Image::isNull() const
{
    return bool(_data);
}

std::shared_ptr<char> Image::data() const
{
    return _data;
}
