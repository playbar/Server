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

net_handle_t netlib_connect(const char *server_ip, uint16_t port,
                            callback_t callback, void *callback_data)
{
    CBaseSocket *pSocket = new CBaseSocket();
    if( NULL == pSocket )
    {
        return NETLIB_INVALID_HANDLE;
    }
    
    net_handle_t handle = pSocket->Connect(server_ip, port, callback, callback_data);
    if( handle == NETLIB_INVALID_HANDLE)
    {
        delete pSocket;
    }
    return handle;
}

int netlib_send( net_handle_t handle, void *buf, int len)
{
    CBaseSocket *pSocket = FindBaseSocket(handle);
    if( NULL == pSocket)
    {
        return NETLIB_ERROR;
    }
    int ret = pSocket->Send(buf, len);
    pSocket->ReleaseRef();
    return ret;
}

int netlib_recv( net_handle_t handle, void *buf, int len)
{
    CBaseSocket *pSocket = FindBaseSocket(handle);
    if( NULL == pSocket)
    {
        return NETLIB_ERROR;
    }
    int ret = pSocket->Recv(buf, len);
    pSocket->ReleaseRef();
    return ret;
}




