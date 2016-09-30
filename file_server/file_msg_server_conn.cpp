//
//  file_msg_server_conn.cpp
//  Server
//
//  Created by mac on 16/9/29.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "file_msg_server_conn.h"

#include "base/pb/protocol/IM.Server.pb.h"
#include "base/pb/protocol/IM.Other.pb.h"

#include "base/im_conn_util.h"

#include "config_util.h"
#include "transfer_task.h"
#include "transfer_task_manager.h"

using namespace IM::BaseDefine;

static ConnMap_t g_file_msg_server_conn_map;

void FileMsgServerConnCallback(void *callback_data, uint8_t msg, uint32_t handle, void *param)
{
    if( NETLIB_MSG_CONNECT == msg )
    {
        FileMsgServerConn *conn = new FileMsgServerConn();
        conn->OnConnect(handle);
    }else{
        log("!!!error msg:%d ", msg);
    }
}




