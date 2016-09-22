//
//  login_server.cpp
//  Server
//
//  Created by mac on 16/8/9.
//  Copyright © 2016年 mac. All rights reserved.
//

#include <stdio.h>
#include "LoginConn.h"
#include "netlib.h"
#include "ConfigFileReader.h"
#include "version.h"
#include "HttpConn.h"
#include "ipparser.h"

IpParser *pIpParser = NULL;
string strMsfsUrl;
string strDiscovery;

void client_callback(void *callback_data, uint8_t msg, uint32_t handle, void *pParam)
{
    if( NETLIB_MSG_CONNECT == msg )
    {
        CLoginConn *pConn = new CLoginConn();
    }
}

void test()
{
    int maxLevel = 7;
    int i = 0;
    int j = 0;
    for( i = 0; i < maxLevel; ++i)
    {
        for(j = 0; j < (maxLevel - i -1); ++j)
            printf(" ");
        for (j = 0; j <=i; ++j) {
            if( i == (maxLevel)/2)
                printf("#");
            else
                printf("*");
        }
        printf("\n");
    }
}

int main( int argc, char *argv[]){
    test();
    int i = 0;
    printf("server version:%d", i);
    return 0;
}
