#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "ImPduBase.h"

namespace DB_PROXY
{
    void doLogin(CImPdu* pPdu, uint32_t conn_uuid);
};


#endif /* LOGIN_H_ */
