#ifndef __RECENTSESSION_H__
#define __RECENTSESSION_H__

#include "ImPduBase.h"

namespace DB_PROXY
{
    void getRecentSession(CImPdu* pPdu, uint32_t conn_uuid);
    void deleteRecentSession(CImPdu* pPdu, uint32_t conn_uuid);

};


#endif /* __RECENTSESSION_H__ */
