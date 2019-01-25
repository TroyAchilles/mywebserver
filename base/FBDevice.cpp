#include "FBDevice.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Debug.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

FBDevice::FBDevice(std::string pathname)
    : _devname(pathname), _fd(-1)
{
}

bool FBDevice::open(int oflag)
{
//    struct fb_fix_screeninfo finfo;
//    ioctl(_fd, FBIOGET_FSCREENINFO, &finfo);
    if (isExist() && !isOpen())
    {
        if ((_fd = ::open(_devname.c_str(), oflag)) != -1
                && ioctl(_fd, FBIOGET_VSCREENINFO, &_vinfo) != -1)
        {
//            if (0 != ftruncate(_fd, _vinfo.xres * _vinfo.yres * _vinfo.bits_per_pixel / 8))
            //do nothing;
        }
        else
        {
            unix_error();
        }
    }

    return (_fd != -1);
}

bool FBDevice::close()
{
    if (-1 != _fd)
    {
        if (0 !=  ::close(_fd))
            unix_error();
        else
            _fd = -1;
    }
    return munmapFb();
}

bool FBDevice::isExist()
{
    struct stat fileinfo;
    if ( 0 == stat(_devname.c_str(), &fileinfo))
    {
        if (S_ISCHR(fileinfo.st_mode))
            return true;
        else
            fprintf(stderr, "%s is not character device\n", _devname.c_str());
    }
    else
    {
        unix_error();
    }

    return false;
}

bool FBDevice::isOpen()
{
    return (_fd != -1);
}

#include <string.h>
FBDevice::MmapInfo FBDevice::mmapFb()
{
    if (isOpen() && !_mmapinfo)  //to avoid fb was repeated map;
    {
        PD(_vinfo.xres * _vinfo.yres * (_vinfo.bits_per_pixel / 8));
        _mmapinfo.ptr = (char*)mmap(NULL, _vinfo.xres * _vinfo.yres * (_vinfo.bits_per_pixel / 8), PROT_READ, MAP_SHARED, _fd, 0);
        if (_mmapinfo.ptr == MAP_FAILED)
        {
            unix_error();
            _mmapinfo.ptr = NULL;
            _mmapinfo.bmaped = false;
        }
        else
        {
            PD(_vinfo.xres);
            PD(_vinfo.yres);
            _mmapinfo.xres = _vinfo.xres;
            _mmapinfo.yres = _vinfo.yres;
            _mmapinfo.bpp = _vinfo.bits_per_pixel / 2;
            _mmapinfo.bmaped = true;
        }
        PADDR(_mmapinfo.ptr);
    }

    return _mmapinfo;
}

bool FBDevice::munmapFb()
{
    if (_mmapinfo)
    {
        if (-1 == munmap(_mmapinfo.ptr, _mmapinfo.xres * _mmapinfo.yres))
        {
            unix_error();
            return false;
        }
        else
        {
            _mmapinfo.bmaped = false;
            _mmapinfo.ptr = NULL;
        }
    }
    return true;
}
