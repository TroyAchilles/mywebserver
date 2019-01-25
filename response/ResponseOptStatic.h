/**
 * @file ResponseOptStatic.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#ifndef _RESPONSEOPTSTATIC_H_
#define _RESPONSEOPTSTATIC_H_
#include "ResponseOperator.h"
class ResponseOptStatic : public ResponseOperator
{
    public:
        ResponseOptStatic(int fd, string filename);
        ~ResponseOptStatic() = default;

        virtual void pre_respond();
        virtual void do_respond();
    protected:
        virtual const string generatorHeadr();
        const std::string getFiletype();
    private:
};
#endif
