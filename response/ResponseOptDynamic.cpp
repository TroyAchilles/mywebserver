/**
 * @file ResponseOptDynamic.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#include "ResponseOptDynamic.h"

ResponseOptDynamic::ResponseOptDynamic(int fd, string filename, string cgiargs)
    :ResponseOperator(fd, filename), _cgiargs(cgiargs)
{

}

void ResponseOptDynamic::pre_respond()
{

}

void ResponseOptDynamic::do_respond()
{

}

const string ResponseOptDynamic::generatorHeadr()
{
    return ResponseOperator::generatorHeadr();
}
