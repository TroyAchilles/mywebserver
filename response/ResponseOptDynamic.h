/**
 * @file ResponseOptDynamic.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#ifndef _RESPONSEOPTDYNAMIC_H_
#define _RESPONSEOPTDYNAMIC_H_
#include "ResponseOperator.h"
class ResponseOptDynamic : public ResponseOperator
{
    public:
        ResponseOptDynamic(int fd, string filename, string cgiargs);
        ~ResponseOptDynamic() = default;

        virtual void pre_respond();
        virtual void do_respond();
    protected:
        virtual const string generatorHeadr();
    private:
        string          _cgiargs;
};
#endif
