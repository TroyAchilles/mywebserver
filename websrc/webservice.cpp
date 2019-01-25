/**
 * @file webservice.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-11
 */
#include "webservice.h"
#include <string.h>
#include <cerrno>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <sstream>
#include <memory>
#include "Request.h"
#include "Socket.h"
#include <unistd.h>
#include "Debug.h"

WebService::WebService()
    :m_servicefd(SocketHelper::unvalid_fd)
{

}

WebService::~WebService()
{
    if (m_servicefd != SocketHelper::unvalid_fd) 
    {
        ::close(m_servicefd);
    }
}

void WebService::listen(int port)
{
    m_servicefd = SocketHelper::listen("0.0.0.0", port);
}

int WebService::accept()
{
    return SocketHelper::accept(m_servicefd, NULL, NULL);
}

void WebService::exit()
{

}

void WebService::handle_client(int connfd)
{
    std::string&& request = SocketHelper::recv_str(connfd);
    auto tp = HttpHelper::parse_head(request);
    try{
        auto req = RequestFactory.produce(std::get<0>(tp), connfd, std::get<0>(tp), std::get<1>(tp), std::get<2>(tp));
        req->doRespon();
    }
    catch(...)
    {
        ::close(connfd);
        std::cout << "throw somethin...\n";
    }
    ::close(connfd);
    std::cout << request;
}

void WebService::responed_http(const int& s, tuple<string, string, string> header)
{
    D_UNUSED(s);
    if ("GET" == std::get<0>(header))
    {
        auto uri = std::get<1>(header);
        if (uri == "/tmp/screenshot")
        {
            std::cout << "screen capture\n";
        }
        else if (uri == "/tmp/log")
        {
            std::cout << "show log\n";
        }
        else
        {
            std::cout << "unknow request\n";
        }
    }
}
   
tuple<string, string, string> HttpHelper::parse_head(const string& request)
{
    Splite splite(request);
    std::string method, uri, version;
    if (splite(' ', method) && splite(' ', uri) && splite('\r', version))
        return std::make_tuple(method, uri, version);

    return tuple<string, string, string>();
}
    
string HttpHelper::generateResponHeader(int err)
{
    static map<int, string> errno_map = {
        {200, "OK"},
        {404, "Not found"},
        {200, "Forbidden"},
        {333, "Unknow"},
    };
  
    if (errno_map.find(err) == errno_map.end())
        err = 333;
    std::stringstream os;
    os  << "HTTP/1.1 "
        << err
        << " "
        << errno_map[err]
        << " "
        << "Server: Dcl Web Server\r\n";
    std::cout << os.str();
    return os.str();
}
