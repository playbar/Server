#ifndef __PUSH_SERVER_HANDLER_H__
#define __PUSH_SERVER_HANDLER_H__

#include <stdio.h>
#include "socket/base_handler.hpp"

class CPushServerHandler : public CBaseHandler
{
public:
    CPushServerHandler() {}
    virtual ~CPushServerHandler() {}
    
    void OnAccept(uint32_t nsockid, S_SOCKET sock, const char* szIP, int32_t nPort);
    void OnClose(uint32_t nsockid);
private:
};

#endif /* defined(__PUSH_SERVER_HANDLER_H__) */
