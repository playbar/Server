#ifndef __PUSH_APP_H__
#define __PUSH_APP_H__


#include <stdio.h>
#include "type/base_type.h"
#include "socket/epoll_io_loop.h"

class CPushApp
{
public:
    CPushApp();
    virtual ~CPushApp();
    
    static CPushApp* GetInstance();
    
    BOOL Init();
    BOOL UnInit();
    BOOL Start();
    BOOL Stop();
    
    CEpollIOLoop& GetIOLoop() { return m_io; }
private:
    BOOL    m_bInit;
    CEpollIOLoop m_io;
};


#endif /* defined(__PUSH_APP_H__) */
