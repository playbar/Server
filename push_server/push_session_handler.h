#ifndef __PUSH_SESSION_HANDLER_H__
#define __PUSH_SESSION_HANDLER_H__

#include <stdio.h>
#include "socket/base_handler.hpp"
#include "pdu_msg.h"

class CPushSessionHandler : public CBaseHandler
{
public:
    CPushSessionHandler() { m_NotificationID = 0; }
    virtual ~CPushSessionHandler() {};
    
    virtual void OnException(uint32_t nsockid, int32_t nErrorCode);
    
    virtual void OnClose(uint32_t nsockid);
    
    virtual void OnRecvData(const char* szBuf, int32_t nBufSize);
    
private:
    void _HandlePushMsg(const char* szBuf, int32_t nBufSize);
    void _HandleHeartBeat(const char* szBuf, int32_t nBufSize);
private:
    uint64_t m_NotificationID;
    CPduMsg m_Msg;
    
};

#endif /* defined(__PUSH_SESSION_HANDLER_H__) */
