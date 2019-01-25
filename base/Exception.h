/**
 * @file Exception.h
 * @brief
 * @author dongchenlong
 * @version v1.0.0.0
 * @date 2018-09-14
 */
#include <string>

struct Exception
{
    Exception(const std::string& errNum,
            const std::string& shortMsg,
            const std::string& longMsg)
        :_errno(errNum), _smsg(shortMsg), _lmsg(longMsg)
    {

    }

    virtual ~Exception() = default;

    std::string             _errno;
    std::string             _smsg;
    std::string             _lmsg;
};
