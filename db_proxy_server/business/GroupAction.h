#ifndef __GROUPACTION_H__
#define __GROUPACTION_H__

#include "ImPduBase.h"

namespace DB_PROXY
{

    void createGroup(CImPdu* pPdu, uint32_t conn_uuid);
    
    void getNormalGroupList(CImPdu* pPdu, uint32_t conn_uuid);
    
    void getGroupInfo(CImPdu* pPdu, uint32_t conn_uuid);
    
    void modifyMember(CImPdu* pPdu, uint32_t conn_uuid);
    
    void setGroupPush(CImPdu* pPdu, uint32_t conn_uuid);
    
    void getGroupPush(CImPdu* pPdu, uint32_t conn_uuid);

};



#endif /* __GROUPACTION_H__ */
