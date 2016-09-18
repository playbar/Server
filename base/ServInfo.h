//
//  ServInfo.hpp
//  Server
//
//  Created by mac on 16/9/18.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef SERVINFO_H_
#define SERVINFO_H_

#include <stdio.h>
#include "util.h"
#include "imconn.h"
#include "ConfigFileReader.h"

#define MAX_RECONNECT_CNT 64
#define MIN_RECONNECT_CNT 4

typedef struct{
    string      server_ip;
    uint16_t    server_port;
    uint32_t    idle_cnt;
    uint32_t    reconnect_cnt;
    CImConn    *serv_conn;
}serv_info_t;

template <class T>
void serv_init(serv_info_t *server_list, uint32_t server_count)
{
    for( uint32_t i = 0; i < server_count; ++i)
    {
        T *pConn = new T();
        pConn->Connect(server_list[i].server_ip.c_str(), server_list[i].server_port, i);
        server_list[i].serv_conn = pConn;
        server_list[i].idle_cnt = 0;
        server_list[i].reconnect_cnt = MIN_RECONNECT_CNT / 2;
    }
}



#endif /* ServInfo_hpp */
