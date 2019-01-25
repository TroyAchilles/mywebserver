#pragma once
#include <string>
#include <fcntl.h>
#include <linux/fb.h>
#include "factory.h"

class FBDevice
{
    public:
        struct MmapInfo
        {
            MmapInfo()
                :ptr(NULL), xres(0), yres(0), bpp(1), bmaped(false)
            {}
            char* 	ptr;
            int 	xres;
            int 	yres;
            int 	bpp; //bit per pexil
            bool 	bmaped;
            explicit operator bool() { return bmaped; }
        };

    public:
        FBDevice(std::string pathname);
        FBDevice(const FBDevice& item) = delete;
        bool open(int oflag = O_RDONLY);
        bool close();
        bool isExist();
        bool isOpen();
        int getFd(){ return _fd; }
        MmapInfo mmapFb();
        bool munmapFb();

    private:
        std::string 						_devname;
        int 								_fd;
        MmapInfo 							_mmapinfo;
        struct fb_var_screeninfo 			_vinfo;
};

#define factoryFBdevice factory<FBDevice, std::string>::instance()
