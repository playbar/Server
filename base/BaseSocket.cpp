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

CBaseSocket::CBaseSocket()
{
    m_socket = INVALID_SOCKET;
    m_state = SOCKET_STATE_IDLE;
}

CBaseSocket::~CBaseSocket()
{
    
}
int CBaseSocket::Listen(const char *server_ip, uint16_t port, callback_t callback, void *callback_data)
{
    m_local_ip = server_ip;
    m_local_port = port;
    m_callback = callback;
    m_callback_data = callback_data;
    
    m_socket = socket( AF_INET, SOCK_STREAM, 0 );
    if( m_socket == INVALID_SOCKET )
    {
        printf("socket failed, err_code=%d\n", _GetErrorCode());
        return NETLIB_ERROR;
    }
    _SetReuseAddr(m_socket);
    _SetNonblock(m_socket);
    
    sockaddr_in serv_addr;
    _SetAddr( server_ip, port, &serv_addr );
    int ret = ::bind(m_socket, (sockaddr*)&serv_addr, sizeof( serv_addr));
    if( ret == SOCKET_ERROR)
    {
        log("bind failed, err_code=%d", _GetErrorCode());
        closesocket( m_socket);
        return NETLIB_ERROR;
    }
    
    ret = listen(m_socket, 64);
    if( ret == SOCKET_ERROR )
    {
        log("listen failed, err_code=%d", _GetErrorCode() );
        closesocket(m_socket);
        return NETLIB_ERROR;
    }
    
    m_state = SOCKET_STATE_LISTENING;
    
    log("CBaseSocket::Listen on %s:%d", server_ip, port);
    
    AddBaseSocket(this);
    CEventDispatch::Instance()->AddEvent(m_socket, SOCKET_READ | SOCKET_EXCEP);
    return NETLIB_OK;
    
}

net_handle_t CBaseSocket::Connect(const char *server_ip, uint16_t port, callback_t callback, void *callback_data)
{
    log("CBaseSocket::Connect, server_ip=%s, port=%d", server_ip, port);
    
    m_remote_ip = server_ip;
    m_remote_port = port;
    m_callback = callback;
    m_callback_data = callback_data;
    
    m_socket = socket( AF_INET, SOCK_STREAM, 0 );
    if( m_socket == INVALID_SOCKET)
    {
        log("socket failed, err_code=%d", _GetErrorCode());
        return NETLIB_INVALID_HANDLE;
    }
    
    _SetNonblock(m_socket);
    _SetNoDelay(m_socket );
    sockaddr_in serv_addr;
    _SetAddr( server_ip, port, &serv_addr );
    int ret = connect( m_socket, (sockaddr*)&serv_addr, sizeof( serv_addr));
    if((ret == SOCKET_ERROR) && (!_IsBlock(_GetErrorCode())))
    {
        log("connect failed, err_code=%d", _GetErrorCode());
        closesocket(m_socket);
        return NETLIB_INVALID_HANDLE;
    }
    
    m_state = SOCKET_STATE_CONNECTING;
    AddBaseSocket(this);
    CEventDispatch::Instance()->AddEvent(m_socket, SOCKET_ALL);
    
    return (net_handle_t)m_socket;
    
}



