//
//  ImPduBase.hpp
//  Server
//
//  Created by mac on 16/9/7.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef IMPDUBASE_H_
#define IMPDUBASE_H_

#include <stdio.h>

#include "UtilPdu.h"
#include "google/protobuf/message_lite.h"

#define IM_PDU_HEADER_LEN 16
#define IM_PDU_VERSION 1

#define ALLOC_FAIL_ASSERT(p) if( NULL == p ){ \
throw CPduException(m_pdu_header.service_id, m_pdu_header.command_id, ERROR_CODE_ALLOC_FAILED, "allocate failed"); \
}

#define CHECK_PB_PARSE_MSG(ret){ \
    if( ret == false )\
    {\
        log("parse pb msg failed."); \
        return;\
    }\
}

#define DLL_MODIFIER

typedef struct{
    uint32_t length;
    uint16_t version;
    uint16_t flag;
    uint16_t service_id;
    uint16_t command_id;
    uint16_t seq_num;
    uint16_t reversed;
}PduHeader_t;

class DLL_MODIFIER CImPdu
{
public:
    CImPdu();
    virtual ~CImPdu();
    
    uchar_t *GetBuffer();
    uint32_t GetLength();
    uchar_t *GetBodyData();
    uint32_t GetBodyLength();
    
    uint16_t GetVersion(){ return m_pdu_header.version;}
    uint16_t GetFlag() { return m_pdu_header.flag; }
    uint16_t GetServiceId() { return m_pdu_header.service_id; }
    uint16_t GetCommandId() { return m_pdu_header.command_id; }
    uint16_t GetSeqNum() { return m_pdu_header.seq_num; }
    uint32_t GetReversed() { return m_pdu_header.reversed; }
    
    void SetVersion( uint16_t version);
    void SetFlag(uint16_t flag);
    void SetServiceId(uint16_t service_id);
    void SetCommandId(uint16_t command_id);
    void SetError( uint16_t error);
    void SetSeqNum(uint16_t seq_num);
    void SetREversed( uint32_t reversed);
    void WriteHeader();
    
    static bool IsPduAvailable( uchar_t *buf, uint32_t len, uint32_t &pdu_len);
    static CImPdu *ReadPdu( uchar_t *buf, uint32_t len);
    void Write( uchar_t *buf, uint32_t len){ m_buf.Write((void*)buf, len);}
    int ReadPduHeader( uchar_t *buf, uint32_t len);
    void SetPBMsg( const google::protobuf::MessageLite *msg);
    
    
protected:
    CSimpleBuffer m_buf;
    PduHeader_t m_pdu_header;
    
};


#endif /* ImPduBase_hpp */
