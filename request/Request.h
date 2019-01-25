/**
 * @file Request.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-13
 */
#pragma once
#include <string>
#include <iostream>
#include "factory.h"

using namespace std;
class Request
{
    public:
        Request(int fd, string method, string uri, string version) 
            :m_fd(fd),m_method(method),m_uri(uri),m_version(version)
        { }

        virtual ~Request() = default; 
    public:
        virtual void doRespon()  = 0;
    protected:
        int         m_fd;
        string      m_method;
        string      m_uri;
        string      m_version;
};

#define RequestFactory factory<Request, int, string, string, string>::instance()
#define REGISTER_RequestFactory(T, key) static factory<Request, int, string, string, string>::register_t<T> register_##T##_(key);
