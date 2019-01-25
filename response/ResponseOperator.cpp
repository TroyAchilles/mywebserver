/**
 * @file ResponseOperator.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#include "ResponseOperator.h"
#include "Exception.h"
#include "Debug.h"
ResponseOperator::ResponseOperator(int fd, string filename)
    :_fd(fd), _file(filename)
{

}
        
void ResponseOperator::pre_respond()
{
    if (stat(_file.c_str(), &_stat) < 0)
        throw Exception("404", "Not found", "Tiny couldn't find this file");

    if (!S_ISREG(_stat.st_mode) || !(S_IRUSR & _stat.st_mode))
        throw Exception("403", "Forbidden", "No read permission");
}
        
void ResponseOperator::do_respond()
{

}
        
const string ResponseOperator::generatorHeadr()
{
    return "HTTP/1.1 200 OK\r\n" + std::string("Server: Zoey Web Server\r\n");
}
