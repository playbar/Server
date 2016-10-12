#ifndef __MESSAGECOUTENT_H__
#define __MESSAGECOUTENT_H__

#include "ImPduBase.h"

namespace DB_PROXY
{

    void getMessage(CImPdu* pPdu, uint32_t conn_uuid);

    void sendMessage(CImPdu* pPdu, uint32_t conn_uuid);
    
    void getMessageById(CImPdu* pPdu, uint32_t conn_uuid);
    
    void getLatestMsgId(CImPdu* pPdu, uint32_t conn_uuid);
};

#endif /* MESSAGECOUTENT_H_ */
