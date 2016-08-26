//
//  BaseSocket.cpp
//  Server
//
//  Created by mac on 16/8/11.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "BaseSocket.h"
#include "EventDispatch.h"

typedef hash_map<net_handle_t, CBaseSocket*>SocketMap;
SocketMap g_socket_map;

void AddBaseSocket( CBaseSocket *pSocket){
    g_socket_map.insert(make_pair((net_handle_t)pSocket->GetSocket(), pSocket));
}

void RemoveBaseSocket(CBaseSocket *pSocket)
{
    g_socket_map.erase((net_handle_t)pSocket->GetSocket());
}

CBaseSocket *FindBaseSocket( net_handle_t fd )
{
    CBaseSocket *pSocket = NULL;
    SocketMap::iterator iter = g_socket_map.find(fd);
    if( iter != g_socket_map.end() )
    {
        pSocket = iter->second;
        pSocket->AddRef();
    }
    return pSocket;
}

//////////////





