/**
 * @file ResponseOptStatic.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#include <iostream> 
#include <sstream>
#include "response/ResponseOptStatic.h"
#include "Socket.h"
#include "Debug.h"
ResponseOptStatic::ResponseOptStatic(int fd, string filename)
    :ResponseOperator(fd, filename)
{

}
        
void ResponseOptStatic::pre_respond()
{
    ResponseOperator::pre_respond();
}

void ResponseOptStatic::do_respond()
{
    SocketHelper::send_str(_fd, generatorHeadr());
    SocketHelper::send_file(_fd, _file);
}
        
const string ResponseOptStatic::generatorHeadr()
{
    std::stringstream os;
    os << ResponseOperator::generatorHeadr() 
        << std::string("Content-length: ")
		<< _stat.st_size
	    << "\r\n"
		<< std::string("Content-type: ")
		<< getFiletype() 
        << "\r\n\r\n";
    PS(os.str().c_str());
    return os.str();
}

const std::string ResponseOptStatic::getFiletype()
{
    /** should use regular expression **/

    if (_file.find(".html") != string::npos)
		return std::string("text/html");
    else if (_file.find(".gif") != string::npos)
        return std::string("image/gif");
    else if (_file.find(".jpg") != string::npos)
        return std::string("image/jpeg");
    else if (_file.find(".png") != string::npos)
        return std::string("image/png");
    else if (_file.find(".css") != string::npos)
        return std::string("text/css");
    else if (_file.find(".js") != string::npos)
        return std::string("text/javascript");
    else
		return std::string("text/plain");
}
