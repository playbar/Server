//
//  HttpConn.cpp
//  Server
//
//  Created by mac on 16/9/19.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "HttpConn.h"
#include "json/json.h"
#include "LoginConn.h"
#include "HttpParserWrapper.h"
#include "ipparser.h"

static HttpConnMap_t g_http_conn_map;

extern map<uint32_t, msg_serv_info_t*> g_msg_serv_info;

extern IpParser *pIpParser;
extern string strMsfsUrl;
extern string strDiscovery;

static uint32_t g_conn_handle_generator = 0;

CHttpConn *FindHttpConnByHandle(uint32_t conn_handle)
{
    CHttpConn *pConn = NULL;
    HttpConnMap_t::iterator it = g_http_conn_map.find(conn_handle);
    if( it != g_http_conn_map.end() )
    {
        pConn = it->second;
    }
    return pConn;
}

void httpconn_callback(void *callback_data, uint8_t msg, uint32_t handle, uint32_t uParam, void *pParam)
{
    NOTUSED_ARG(uParam);
    NOTUSED_ARG(pParam);
    
    uint32_t conn_handle = *((uint32_t*)(&callback_data));
    CHttpConn *pConn = FindHttpConnByHandle(conn_handle);
    if( pConn == NULL )
    {
        return;
    }
    switch (msg)
    {
        case NETLIB_MSG_READ:
            pConn->OnRead();
            break;
        case NETLIB_MSG_WRITE:
            pConn->OnWrite();
            break;
        case NETLIB_MSG_CLOSE:
            pConn->Close();
            break;
            
        default:
            log("!!!httpconn_callback error msg: %d ", msg);
            break;
    }
    return;
}

void http_conn_timer_callback(void *callback_data, uint8_t msg, uint32_t handle, void *pParam)
{
    CHttpConn *pConn = NULL;
    HttpConnMap_t::iterator it, it_old;
    uint64_t cur_time = get_tick_count();
    for (it = g_http_conn_map.begin(); it != g_http_conn_map.end(); )
    {
        it_old = it;
        ++it;
        pConn = it_old->second;
        pConn->OnTime(cur_time);
    }
    return;
}

void init_http_conn()
{
    netlib_register_timer(http_conn_timer_callback, NULL, 1000);
}

CHttpConn::CHttpConn()
{
    m_busy = false;
    m_sock_handle = NETLIB_INVALID_HANDLE;
    m_state = CONN_STATE_IDLE;
    m_last_send_tick = m_last_send_tick = get_tick_count();
    m_conn_handle = ++g_conn_handle_generator;
    if(m_conn_handle == 0)
    {
        m_conn_handle = ++g_conn_handle_generator;
    }
}


CHttpConn::~CHttpConn()
{
    
}

int CHttpConn::Send(void *data, int len)
{
    m_last_send_tick = get_tick_count();
    if( m_busy)
    {
        m_out_buf.Write(data, len);
        return len;
    }
    
    int ret = netlib_send(m_sock_handle, data, len);
    if( ret < 0)
    {
        ret = 0;
    }
    
    if (ret < len)
    {
        m_out_buf.Write((char*)data + ret, len - ret);
        m_busy = true;
    }
    else
    {
        OnWriteComplete();
    }
    return len;
}

void CHttpConn::Close()
{
    m_state = CONN_STATE_CLOSED;
    
    g_http_conn_map.erase(m_conn_handle);
    netlib_close(m_sock_handle);
    ReleaseRef();
    return;
}

void CHttpConn::OnConnect(net_handle_t handle)
{
    
}

void CHttpConn::OnRead()
{
    
}

void CHttpConn::OnWrite()
{
    
}

void CHttpConn::OnClose()
{
    
}

void CHttpConn::OnTime(uint64_t curr_tick)
{
    
}

void CHttpConn::_HandleMsgServRequest(string &url, string &post_data)
{
    
}

void CHttpConn::OnWriteComplete()
{
    
}