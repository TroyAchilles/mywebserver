/**
 * @file GETRequest.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-13
 */
#ifndef _GETREQUEST_H_
#define _GETREQUEST_H_
#include "Request.h"
class GETRequest : public Request
{
    public:
        GETRequest(int fd, string method, string uri, string version);
        virtual ~GETRequest();

        virtual void doRespon();
    private:
        tuple<string, string, bool> parseUri();
};
REGISTER_RequestFactory(GETRequest, "GET")
#endif
