/**
 * @file ResponseOperator.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#ifndef _RESPONSEOPERATOR_H_
#define _RESPONSEOPERATOR_H_
#include <string>
#include <sys/stat.h>
using namespace std;

/**提供响应操作的接口 */
class ResponseOperator
{
    public:
        ResponseOperator(int fd, string filename);
        virtual ~ResponseOperator() = default;

        virtual void pre_respond() = 0;
        virtual void do_respond() = 0;
    protected:
        virtual const string generatorHeadr() = 0;
    protected:
        int                 _fd;
        string              _file;
        struct stat         _stat;
};
#endif
