//
//  EventDispatch.cpp
//  Server
//
//  Created by mac on 16/8/18.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "EventDispatch.h"
#include "BaseSocket.h"

#define MIN_TIMER_DURATION 100

CEventDispatch* CEventDispatch::m_pEventDispatch = NULL;

CEventDispatch::CEventDispatch(){
    running = false;
#ifdef __APPLE__
    m_kqfd = kqueue();
    if( m_kqfd == -1 ){
        log("kqueue failed");
    }
#else
    m_epfd = epoll_create(1024);
    if( m_epfd == -1 ){
        log("epoll_create failed");
    }
#endif
    return;
}

