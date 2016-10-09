#ifndef __PUSH_SERVER_H__
#define __PUSH_SERVER_H__

#include <stdio.h>
#include <string>
#include <memory>
#include "socket/tcp_server.h"
#include "socket/epoll_io_loop.h"
#include "push_server_handler.h"

using namespace std;

class CPushServer : public std::enable_shared_from_this<CPushServer>
{
public:
    CPushServer(CEpollIOLoop& io);
    virtual ~CPushServer();
    
    void SetListenIP(const char* listen_ip) { m_strListenIP = listen_ip; }
    string GetListenIP() { return m_strListenIP; }
    void SetPort(uint32_t port) { m_nPort = port; }
    uint32_t GetPort() { return m_nPort; }
    CEpollIOLoop& GetIOLoop() { return m_io; }

    BOOL Start();
    BOOL Stop();
    
private:
    string m_strListenIP;
    uint32_t m_nPort;
    
    CTCPServer* m_pServer;
    CEpollIOLoop& m_io;
    CPushServerHandler m_handler;
};

typedef std::shared_ptr<CPushServer> push_server_ptr;

#endif /* defined(__PUSH_SERVER_H__) */
