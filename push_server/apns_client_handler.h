#ifndef __APNS_CLIENT_HANDLER_H__
#define __APNS_CLIENT_HANDLER_H__

#include <stdio.h>
#include "apns_msg.h"
#include "socket/base_handler.hpp"

class CAPNSClientHandler : public CBaseHandler
{
public:
    CAPNSClientHandler() {}
    virtual ~CAPNSClientHandler() {}
    
    virtual void OnException(uint32_t nsockid, int32_t nErrorCode);
    
    virtual void OnClose(uint32_t nsockid);
    
    virtual void OnConnect(uint32_t nsockid);
    
    virtual void OnSSLConnect(uint32_t nsockid);

    virtual void OnRecvData(const char* szBuf, int32_t nBufSize);
    
protected:
    CAPNSGateWayResMsg m_Msg;
};

#endif /* defined(__APNS_CLIENT_HANDLER_H__) */
