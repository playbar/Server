//
//  im_conn_util.hpp
//  Server
//
//  Created by mac on 16/9/7.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef BASE_IM_CONN_UTIL_H_
#define BASE_IM_CONN_UTIL_H_

#include <stdio.h>
#include "base/ostype.h"

namespace google {namespace protobuf{
    class MessageLite;
}}

class CImConn;

int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid,
                    const ::google::protobuf::MessageLite* message);
int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid, uint16_t seq_num,
                    const ::google::protobuf::MessageLite* message);
int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid, uint16_t seq_num,
                    uint16_t error, const ::google::protobuf::MessageLite* message);


#endif /* im_conn_util_hpp */
