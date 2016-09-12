//
//  netlib.cpp
//  Server
//
//  Created by mac on 16/9/9.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "netlib.h"
#include "BaseSocket.h"
#include "EventDispatch.h"

int netlib_init()
{
    int ret = NETLIB_OK;
    return ret;
}


int netlib_destroy()
{
    int ret = NETLIB_OK;
    return ret;
}

int netlib_listen(const char *server_ip, uint16_t port,
                  callback_t callback, void *callback_data)
{
    CBaseSocket *pSocket = new CBaseSocket();
    if( NULL == pSocket )
    {
        return NETLIB_ERROR;
    }
    int ret = pSocket->Listen(server_ip, port, callback, callback_data);
    if( ret == NETLIB_ERROR){
        delete pSocket;
    }
    return ret;
}


