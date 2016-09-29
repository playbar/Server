//
//  config_util.hpp
//  Server
//
//  Created by mac on 16/9/29.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef FILE_SERVER_CONFIG_UTIL_H_
#define FILE_SERVER_CONFIG_UTIL_H_

#include <stdio.h>
#include "list"

#include "base/singleton.h"
#include "base/pb/protocol/IM.BaseDefine.pb.h"

class ConfigUtil : public Singleton<ConfigUtil>
{
public:
    ~ConfigUtil(){}
    
    void AddAddress(const char *ip, uint16_t port);
    const std::list<IM::BaseDefine::IpAddr> &GetAddressList()const{
        return addrs_;
    }
    
    void SetTaskTimeout(uint32_t timeout) { task_timeout_ = timeout;}
    uint32_t GetTaskTimeout() const {return task_timeout_;}
    
private:
    friend class Singleton<ConfigUtil>;
    
    ConfigUtil() : task_timeout_(3600){}
    
    std::list<IM::BaseDefine::IpAddr> addrs_;
    uint32_t task_timeout_;
    
};

#endif /* config_util_hpp */
