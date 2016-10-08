//
//  im_conn_util.cpp
//  Server
//
//  Created by mac on 16/9/7.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "im_conn_util.h"

#include "imconn.h"
#include "ImPduBase.h"

int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid,
                    const ::google::protobuf::MessageLite* message)
{
    CImPdu pdu;
    
    pdu.SetPBMsg(message);
    pdu.SetServiceId(sid);
    pdu.SetCommandId(cid);
    
    return conn->SendPdu(&pdu);
}

int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid, uint16_t seq_num,
                    const ::google::protobuf::MessageLite* message)
{
    CImPdu pdu;
    
    pdu.SetPBMsg(message);
    pdu.SetServiceId(sid);
    pdu.SetCommandId(cid);
    pdu.SetSeqNum(seq_num);
    
    return conn->SendPdu(&pdu);
}

int SendMessageLite(CImConn* conn, uint16_t sid, uint16_t cid, uint16_t seq_num,
                    uint16_t error, const ::google::protobuf::MessageLite* message)
{
    CImPdu pdu;
    
    pdu.SetPBMsg(message);
    pdu.SetServiceId(sid);
    pdu.SetCommandId(cid);
    pdu.SetSeqNum(seq_num);
    pdu.SetError(error);
    
    return conn->SendPdu(&pdu);
}
