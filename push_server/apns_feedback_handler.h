#ifndef __APNS_FEEDBACK_HANDLE_H__
#define __APNS_FEEDBACK_HANDLE_H__

#include <stdio.h>
#include "socket/base_handler.hpp"
#include "apns_msg.h"

class CAPNSFeedBackHandler : public CBaseHandler
{
public:
    CAPNSFeedBackHandler() {}
    virtual ~CAPNSFeedBackHandler() {}
    
    virtual void OnException(uint32_t nsockid, int32_t nErrorCode);
    
    virtual void OnClose(uint32_t nsockid);
    
    virtual void OnConnect(uint32_t nsockid);
    
    virtual void OnSSLConnect(uint32_t nsockid);
    
    virtual void OnRecvData(const char* szBuf, int32_t nBufSize);
    
private:
    CAPNSFeedBackResMsg m_Msg;
};

#endif /* defined(__APNS_FEEDBACK_HANDLE_H__) */
