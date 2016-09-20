//
//  ipparser.hpp
//  Server
//
//  Created by mac on 16/9/19.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef ipparser_hpp
#define ipparser_hpp

#include <stdio.h>
#include "util.h"

class IpParser
{
public:
    IpParser();
    virtual ~IpParser();
    bool isTelcome(const char *ip);
};

#endif /* ipparser_hpp */
