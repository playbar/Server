#ifndef __LOGINSTRATEGY_H__
#define __LOGINSTRATEGY_H__

#include <iostream>

#include "IM.BaseDefine.pb.h"

class CLoginStrategy
{
public:
    virtual bool doLogin(const std::string& strName, const std::string& strPass,
                         IM::BaseDefine::UserInfo& user) = 0;
};

#endif /*defined(__LOGINSTRATEGY_H__) */
