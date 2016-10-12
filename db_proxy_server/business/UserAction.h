#ifndef __USERACTION_H__
#define __USERACTION_H__

#include "ImPduBase.h"

namespace DB_PROXY
{
    void getUserInfo(CImPdu* pPdu, uint32_t conn_uuid);
    void getChangedUser(CImPdu* pPdu, uint32_t conn_uuid);
    void changeUserSignInfo(CImPdu* pPdu, uint32_t conn_uuid);
    void doPushShield(CImPdu* pPdu, uint32_t conn_uuid);
    void doQueryPushShield(CImPdu* pPdu, uint32_t conn_uuid);
};


#endif /* __USER_ACTION_H__ */
