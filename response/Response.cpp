/**
 * @file Response.cpp
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-13
 */

#include "Response.h"
#include "ResponseOptStatic.h"
#include "ResponseOptDynamic.h"
#include <iostream>
#include "Exception.h"
Response::Response(int fd, string filename, string cgiargs, bool isStc)
{
    if (isStc)
        m_respond = std::make_shared<ResponseOptStatic>(fd, filename);
    else
        m_respond = std::make_shared<ResponseOptDynamic>(fd, filename, cgiargs);
}
        
Response::Response(int fd, tuple<string, string, bool> tp)
    : Response(fd, get<0>(tp), get<1>(tp), get<2>(tp))
{

}
        
void Response::response()
{
    try{
        m_respond->pre_respond();
        m_respond->do_respond();
    }
    catch (Exception& err)
    {
        std::cout << "-----------:" << err._smsg << std::endl;
    }
    catch (std::runtime_error& err)
    {
        std::cout << "-----------:------runtime error";
    }
}

