#include "Debug.h"
#include "webservice.h"
#include "Socket.h"
using namespace std;

int main(int argc, char** argv)
{
    D_UNUSED(argc);
    D_UNUSED(argv);

//    FBDevice dev("/dev/fb0");
//    dev.open(O_RDONLY);
//    auto minfo = dev.mmapFb();
//    Image img(minfo.ptr, minfo.xres, minfo.yres, Image::Format::Format_RGB16);
//    img.save("/usr/local/iDM/Perfect1.bmp", "Bmp", true);
//    img.save("/usr/local/iDM/Perfect2.bmp");
//    dev.close();

    WebService 	webs;
    webs.listen(80);
    while(1)
    {
        int client_fd = webs.accept();
        if (client_fd != SocketHelper::unvalid_fd)
        {
           webs.handle_client(client_fd);
        }
    }

    return 0;
}
