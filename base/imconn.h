//
//  imconn.hpp
//  Server
//
//  Created by mac on 16/9/7.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef IMCONN_H_
#define IMCONN_H_

#include <stdio.h>
#include "netlib.h"
#include "util.h"
#include "ImPduBase.h"

#define SERVER_HEARTBEAT_INTERVAL   5000
#define SERVER_TIMEOUT              30000
#define CLIENT_HEARTBEAT_INTERVAL   30000
#define CLIETN_TIMEOUT              120000
#define MOBILE_CLIENT_TIMEOUT       60000 * 5
#define READ_BUF_SIZE               2048

class CImConn : public CRefObject
{
public:
    CImConn();
    virtual ~CImConn();
    
    bool IsBusy() { return m_busy;}
    
    
protected:
    net_handle_t    m_handle;
    bool            m_busy;
    string          m_peer_ip;
    uint16_t        m_peer_port;
    CSimpleBuffer   m_in_buf;
    CSimpleBuffer   m_out_buf;
    
    bool            m_policy_conn;
    uint32_t        m_recv_bytes;
    uint32_t        m_last_send_tick;
    uint32_t        m_last_recv_tick;
    uint64_t        m_last_all_user_tick;
};



#endif /* imconn_hpp */
