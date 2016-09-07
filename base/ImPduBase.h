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
    
};


#endif /* ImPduBase_hpp */
