#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include "Socket.h"
#include "Debug.h"

int SocketHelper::listen(const std::string& ip, int port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        exit_unix_error("socket");
        return unvalid_fd;
    }

    int reuse = 1;
    int ret = -1;
    if ((ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))) < 0)
    {
        exit_unix_error("setsockopt:");
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        exit_unix_error("bind");
        return unvalid_fd;
    }

    if (::listen(listenfd, 10) < 0)
    {
        exit_unix_error("listen");
        return unvalid_fd;
    }

    return listenfd;
}

int SocketHelper::accept(const int& s, struct sockaddr *addr, socklen_t* addrlen)
{
    int ret = unvalid_fd;
    if ((ret = ::accept(s, addr, addrlen)) < 0)
    {
        exit_unix_error("accept");
        return unvalid_fd;
    }
    return ret;
}

std::string SocketHelper::recv_str(const int& s)
{
    std::string request;
    char buf[8192] = { 0 };
    while (1)
    {
        int ret = ::read(s, buf, sizeof(buf));
        std::cout << ret << std::endl;
        if (ret < 0)
        {
           if (errno != EINTR) 
               break;
        }
        else if (ret == 0)  /* EOF */
        {
            break;
        }
        else
        {
            request.append(buf, ret);
            //std::cout << "--<" << buf[ret-2] << ">--" << std::endl; //\r
            //std::cout << "--<" << buf[ret-1] << ">--" << std::endl; //\n
            if (buf[ret - 2] == '\r' && buf[ret - 1] == '\n')
                break;
            bzero(buf, ret);
        }
    }

    return request;
}
    
int SocketHelper::send_buf(const int& s, const char* buf, size_t len)
{
    size_t nleft = len; 
    size_t nwrite = 0;
    while (nleft > 0)
    {
        int ret = ::write(s, buf + nwrite, nleft);
        if (ret <= 0)
        {
            if (EINTR == errno)
                ret = 0;
            else
                break;
        }
        nleft -= ret;
        nwrite += ret;
    }
    return nwrite;
}

int SocketHelper::send_str(const int& s, const string& str)
{
    return send_buf(s, str.c_str(), str.length());
}

int SocketHelper::send_file(const int& s, const string& file)
{
    struct stat st;
    if (stat(file.c_str(), &st) < 0) 
    {
        exit_unix_error("stat:");
        return -1;  //not found this file
    }
    if (!S_ISREG(st.st_mode) || !(S_IRUSR & st.st_mode))
    {
        exit_unix_error("stat:");
        return -2;  //no permission
    }

    int fd = open(file.c_str(), O_RDONLY, 0);
    if (fd < 0)
    {
        exit_unix_error("open");
        return -3;  //open file failed;
    }

    void* ptr = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    int ret = send_buf(s, (char*)ptr, st.st_size);
    munmap(ptr, st.st_size);
    return ret;
}
    
