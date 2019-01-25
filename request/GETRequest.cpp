/**
 * @file GETRequest.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-13
 */
#include "GETRequest.h"
#include "Response.h"

#define WEBSERVICE_ROOT_PATH "/usr/local/iDM/test-files"


GETRequest::GETRequest(int fd, string method, string uri, string version)
    :Request(fd, method, uri, version)
{

}

GETRequest::~GETRequest()
{

}

void GETRequest::doRespon()
{
    auto ret = parseUri(); 
    Response(m_fd, ret).response();
}

tuple<string, string, bool> GETRequest::parseUri()
{
    string filename, cgiargs;
    bool isStc;

    if (m_uri.find("cgi-bin") != string::npos)
    {   /*解析动态连接*/
        auto pos = m_uri.find_first_of('?');
        if (string::npos != pos)
            cgiargs = m_uri.substr(pos, m_uri.length() - 1);
        isStc = false;
    }
    else
    {   /*解析静态连接*/
        filename = WEBSERVICE_ROOT_PATH + m_uri;
        if (m_uri[m_uri.length() - 1] == '/')
//            filename += "index.html";
            filename += "mainpage.html";
        isStc = true;
    }
    return make_tuple(filename, cgiargs, isStc);
}
