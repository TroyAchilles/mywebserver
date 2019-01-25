/**
 * @file Response.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-13
 */

#ifndef _RESPONSE_H_
#define _RESPONSE_H_
#include <string>
#include <tuple>
#include <memory>
using namespace std;
class ResponseOperator;

class Response
{
    public:
        Response(int fd, string filename, string cgiargs, bool isStc);
        Response(int fd, tuple<string, string, bool> tp);
        ~Response() = default;
        
        void response();
    private:
        shared_ptr<ResponseOperator>       m_respond;
};


#endif
