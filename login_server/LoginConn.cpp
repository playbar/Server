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


