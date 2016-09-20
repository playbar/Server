//
//  ipparser.cpp
//  Server
//
//  Created by mac on 16/9/19.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "ipparser.h"

IpParser::IpParser()
{
    
}

IpParser::~IpParser()
{
    
}

bool IpParser::isTelcome(const char *pIp)
{
    if( pIp == NULL)
    {
        return false;
    }
    CStrExplode strExp((char*)pIp,'.');
    if( strExp.GetItemCnt() != 4 )
    {
        return false;
    }
    return true;
}