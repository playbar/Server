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

int CBaseSocket::Send( void* buf, int len)
{
    if( m_state != SOCKET_STATE_CONNECTED)
    {
        return NETLIB_ERROR;
    }
    
    int ret = send( m_socket, (char*)buf, len, 0);
    if( ret == SOCKET_ERROR){
        int err_code = _GetErrorCode();
        if( _IsBlock( err_code ))
        {
            CEventDispatch::Instance()->AddEvent(m_socket, SOCKET_WRITE);
            ret = 0;
        }
        else
        {
            log("!!!send failed, error code: %d", err_code);
        }
    }
    
    return ret;
    
}

int CBaseSocket::Recv(void *buf, int len)
{
    return recv( m_socket, (char*)buf, len, 0);
}

int CBaseSocket::Close()
{
    CEventDispatch::Instance()->RemoveEvent(m_socket, SOCKET_ALL);
    RemoveBaseSocket(this);
    closesocket(m_socket);
    ReleaseRef();
    return 0;
}

void CBaseSocket::OnRead()
{
    if(m_state == SOCKET_STATE_LISTENING )
    {
        _AcceptNewSocket();
    }
    else
    {
        u_long avail = 0;
        if((ioctlsocket( m_socket, FIONREAD, &avail) == SOCKET_ERROR) || (avail == 0))
        {
            m_callback( m_callback_data, NETLIB_MSG_CLOSE, (net_handle_t)m_socket, NULL);
        }
        else
        {
            m_callback( m_callback_data, NETLIB_MSG_READ, (net_handle_t)m_socket, NULL);
        }
    }
}

void CBaseSocket::OnWrite()
{
    CEventDispatch::Instance()->RemoveEvent(m_socket, SOCKET_WRITE);
    if( m_state == SOCKET_STATE_CONNECTING )
    {
        int error = 0;
        socklen_t len = sizeof( error);
        getsockopt( m_socket, SOL_SOCKET, SO_ERROR, (void*)&error, &len);
        if( error)
        {
            m_callback( m_callback_data, NETLIB_MSG_CLOSE, (net_handle_t)m_socket, NULL);
        }
        else
        {
            m_state = SOCKET_STATE_CONNECTED;
            m_callback( m_callback_data, NETLIB_MSG_CONFIRM, (net_handle_t)m_socket, NULL);
        }
    }
    else
    {
        m_callback( m_callback_data, NETLIB_MSG_WRITE, (net_handle_t)m_socket, NULL);
    }
    
    return;
}

void CBaseSocket::OnClose()
{
    m_state = SOCKET_STATE_CLOSING;
    m_callback( m_callback_data, NETLIB_MSG_CLOSE, (net_handle_t)m_socket, NULL);
}

void CBaseSocket::SetSendBufSize(uint32_t send_size)
{
    int ret = setsockopt( m_socket, SOL_SOCKET, SO_SNDBUF, &send_size, 4 );
    if( ret == SOCKET_ERROR )
    {
        log("set SO_SNDBUF failed for fd=%d", m_socket);
    }
    
    socklen_t len = 4;
    int size = 0;
    getsockopt( m_socket, SOL_SOCKET, SO_SNDBUF, &size, &len);
    log("socket=%d send_buf_size=%d", m_socket, size);
    return;
}

void CBaseSocket::SetRecvBufSize(uint32_t recv_size)
{
    int ret = setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &recv_size, 4);
    if( ret == SOCKET_ERROR)
    {
        log("set SO_RCVBUF failed for fd=%d", m_socket);
    }
    
    socklen_t len = 4;
    int size = 0;
    getsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, &size, &len);
    log("socket=%d recv_buf_size=%d", m_socket, size);
    return;
}

int CBaseSocket::_GetErrorCode()
{
    return errno;
}

bool CBaseSocket::_IsBlock(int error_code)
{
    return ((error_code == EINPROGRESS) || (error_code == EWOULDBLOCK));
}

void CBaseSocket::_SetNonblock(SOCKET fd )
{
    int ret = fcntl(fd, F_SETFL, O_NONBLOCK | fcntl(fd, F_GETFL));
    if( ret == SOCKET_ERROR )
    {
        log("_SetNonblock failed, err_code=%d", _GetErrorCode());
    }
}

void CBaseSocket::_SetReuseAddr(SOCKET fd)
{
    int reuse = -1;
    int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof( reuse));
    if( ret == SOCKET_ERROR )
    {
        log("_SetReuseAddr failed, err_code=%d", _GetErrorCode());
    }
}

void CBaseSocket::_SetNoDelay(SOCKET fd )
{
    int nodelay = 1;
    int ret = setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(nodelay));
    if( ret == SOCKET_ERROR)
    {
        log("_SetNoDelay failed, err_code=%d", _GetErrorCode());
    }
}


void CBaseSocket::_SetAddr(const char *ip, const uint16_t port, sockaddr_in *pAddr)
{
    memset( pAddr, 0, sizeof( sockaddr_in));
    pAddr->sin_family = AF_INET;
    pAddr->sin_port = htons( port);
    
}
