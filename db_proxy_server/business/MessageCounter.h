#ifndef __MESSAGECOUNTER_H__
#define __MESSAGECOUNTER_H__

#include "ImPduBase.h"
namespace DB_PROXY
{

    void getUnreadMsgCounter(CImPdu* pPdu, uint32_t conn_uuid);
    void clearUnreadMsgCounter(CImPdu* pPdu, uint32_t conn_uuid);
    
    void setDevicesToken(CImPdu* pPdu, uint32_t conn_uuid);
    void getDevicesToken(CImPdu* pPdu, uint32_t conn_uuid);
};


#endif /* __MESSAGECOUNTER_H__ */
