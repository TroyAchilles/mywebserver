#pragma once
#include <string>
#include <memory>
using namespace std;
class Image
{
    public:
        enum Format
        {
            Format_Invalid,
            Format_RGB16 = 16,
            Format_RGB888 = 24,
            Format_ARGB32 = 32,
        };

    public:
        Image();
        Image(const char* p, size_t w, size_t h, Format format);
        Image(const Image& img);
        Image &operator=(const Image& right);
        Image &operator=(Image&& right);
        virtual ~Image() = default;

        bool save(const string filename, const string style = "", bool bsync = false) const;
        bool isNull() const;

        size_t w() const { return _w; }
        size_t h() const { return _h; }
        size_t bpp() const { return _bpp; }
        Format format() const { return _format; }
        std::shared_ptr<char> data() const;

    private:
        string _surmiseFormat(const string& filename, const string& format) const;


    private:
        size_t 						_w;
        size_t 						_h;
        size_t 						_bpp;
        Format 						_format;
        std::shared_ptr<char> 		_data;
};
