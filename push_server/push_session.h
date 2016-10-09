#ifndef __PUSH_SESSION_H__
#define __PUSH_SESSION_H__

#include <stdio.h>
#include <memory>
#include "socket/epoll_io_loop.h"
#include "socket/tcp_session_async.h"
#include "push_session_handler.h"

class CPushSession : public std::enable_shared_from_this<CPushSession>
{
public:
    CPushSession(CEpollIOLoop& io, S_SOCKET sock);
    virtual ~CPushSession();
    
    uint32_t GetSocketID() { return m_pSession->GetSocketID(); }
    const char* GetRemoteIP() { return m_pSession->GetRemoteIP(); }
    int32_t GetRemotePort() { return m_pSession->GetRemotePort(); }
    
    BOOL Start();
    BOOL Stop();
    BOOL SendMsg(const char* szMsg, uint32_t nMsgSize);
    
    void SetHeartBeat(uint64_t nHeartBeat) { m_nLastHeartBeat = nHeartBeat; }
    uint64_t GetLastHeartBeat() { return m_nLastHeartBeat; }
private:
    uint64_t m_nLastHeartBeat;
    CTCPSessionAsync* m_pSession;
    CEpollIOLoop& m_io;
    CPushSessionHandler m_handler;
};

typedef std::shared_ptr<CPushSession> push_session_ptr;

#endif /* defined(__PUSH_SESSION_H__) */
