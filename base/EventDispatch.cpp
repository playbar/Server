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

CEventDispatch::~CEventDispatch(){
#ifdef __APPLE__
    close( m_kqfd);
#else
    close(m_epfd);
#endif
    
}

void CEventDispatch::AddTimer(callback_t callback, void *user_data, uint64_t interval)
{
    list<TimerItem*>::iterator it;
    for( it = m_timer_list.begin(); it != m_timer_list.end(); ++it )
    {
        TimerItem *pItem = *it;
        if( pItem->callback == callback && pItem->user_data == user_data )
        {
            pItem->interval = interval;
            pItem->next_tick = get_tick_count() + interval;
            return;
        }
    }
    
    TimerItem *pItem = new TimerItem;
    pItem->callback = callback;
    pItem->user_data = user_data;
    pItem->interval = interval;
    pItem->next_tick = get_tick_count() + interval;
    m_timer_list.push_back(pItem);
    return;
}


