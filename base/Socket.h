/**
 * @file Socket.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <string.h>
#define exit_unix_error(msg)  \
    do{     \
        fprintf(stderr, "(%s: %s) %s:%d\n", (char*)msg, strerror(errno), __FILE__, __LINE__-2);  \
        exit(0);    \
    }while(0);


using namespace std;
struct SocketHelper
{
    static const int unvalid_fd = -1;
    static int listen(const std::string& ip, int port);
    static int accept(const int& s, struct sockaddr *addr, socklen_t* addrlen);
    static std::string recv_str(const int& s);
    static int send_str(const int& s, const string& str);
    static int send_buf(const int& s, const char* buf, size_t len);
    static int send_file(const int& s, const string& file);
};
