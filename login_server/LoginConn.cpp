//
//  LoginConn.cpp
//  Server
//
//  Created by mac on 16/9/19.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "LoginConn.h"
#include "IM.Server.pb.h"
#include "IM.Other.pb.h"
#include "IM.Login.pb.h"
#include "public_define.h"

using namespace IM::BaseDefine;
static ConnMap_t g_client_conn_map;
static ConnMap_t g_msg_serv_conn_map;
static uint32_t  g_total_online_user_cnt = 0;

map<uint32_t, msg_serv_info_t*> g_msg_serv_info;

void login_conn_timer_callback(void *callback_data, uint8_t msg, uint32_t handle, void *pParam)
{
    uint64_t cur_time = get_tick_count();
    for( ConnMap_t::iterator it = g_client_conn_map.begin(); it != g_client_conn_map.end();)
    {
        ConnMap_t::iterator it_old = it;
        ++it;
        CLoginConn *pConn = (CLoginConn*)it_old->second;
        pConn->OnTimer(cur_time);
    }
    
    for (ConnMap_t::iterator it = g_msg_serv_conn_map.begin(); it != g_msg_serv_conn_map.end(); )
    {
        ConnMap_t::iterator it_old = it;
        ++it;
        CLoginConn *pConn = (CLoginConn*)it->second;
        pConn->OnTimer(cur_time);
    }
    return;
}


void init_login_conn()
{
    netlib_register_timer(login_conn_timer_callback, NULL, 1000);
}

CLoginConn::CLoginConn()
{
    
}

CLoginConn::~CLoginConn()
{
    
}

void CLoginConn::Close()
{
    if( m_handle != NETLIB_INVALID_HANDLE)
    {
        netlib_close(m_handle);
        if( m_conn_type == LOGIN_CONN_TYPE_CLIENT)
        {
            g_client_conn_map.erase(m_handle);
        }
        else
        {
            g_msg_serv_conn_map.erase(m_handle);
            
            map<uint32_t, msg_serv_info_t*>::iterator it = g_msg_serv_info.find(m_handle);
            if( it != g_msg_serv_info.end())
            {
                msg_serv_info_t *pMsgServInfo = it->second;
                
                g_total_online_user_cnt -= pMsgServInfo->cur_conn_cnt;
                log("onclose from MsgServer: %s:%u", pMsgServInfo->hostname.c_str(), pMsgServInfo->port);
                delete pMsgServInfo;
                g_msg_serv_info.erase(it);
            }
        }
    }
    ReleaseRef();
}

void CLoginConn::OnConnect2(net_handle_t handle, int conn_type)
{
    
}

void CLoginConn::OnClose()
{
    
}

void CLoginConn::OnTimer(uint64_t curr_tick)
{
    
}

void CLoginConn::HandlePdu(CImPdu *pPdu)
{
    
}

void CLoginConn::_HandleMsgServInfo(CImPdu *pPdu)
{
    
}

void CLoginConn::_HandleUserCntUpdate(CImPdu *pPdu)
{
    
}

void CLoginConn::_HandleMsgServRequest(CImPdu *pPdu)
{
    
}
