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


void CEventDispatch::RemoveTimer(callback_t callback, void *user_data)
{
    list<TimerItem*>::iterator it;
    for( it = m_timer_list.begin(); it != m_timer_list.end(); ++it )
    {
        TimerItem *pItem = *it;
        if( pItem->callback == callback && pItem->user_data == user_data )
        {
            m_timer_list.erase(it);
            delete pItem;
            return;
        }
    }
}

void CEventDispatch::_CheckTimer()
{
    uint64_t curr_tick = get_tick_count();
    list<TimerItem*>::iterator it;
    for( it = m_timer_list.begin(); it != m_timer_list.end(); )
    {
        TimerItem *pItem = *it;
        ++it;
        if( curr_tick >= pItem->next_tick ){
            pItem->next_tick += pItem->interval;
            pItem->callback(pItem->user_data, NETLIB_MSG_TIMER, 0, NULL);
        }
    }
    return;
}

void CEventDispatch::AddLoop(callback_t callback, void *user_data)
{
    TimerItem *pItem = new TimerItem;
    pItem->callback = callback;
    pItem->user_data = user_data;
    m_loop_list.push_back(pItem);
    return;
}

void CEventDispatch::_CheckLoop()
{
    list<TimerItem*>::iterator it;
    for( it = m_loop_list.begin(); it != m_loop_list.end(); ++it )
    {
        TimerItem *pItem = *it;
        pItem->callback( pItem->user_data, NETLIB_MSG_LOOP, 0, NULL );
    }
    return;
}

CEventDispatch *CEventDispatch::Instance()
{
    if( m_pEventDispatch == NULL ){
        m_pEventDispatch = new CEventDispatch();
    }
    return m_pEventDispatch;
}

#ifdef __APPLE__

void CEventDispatch::AddEvent(SOCKET fd, uint8_t socket_event)
{
    struct kevent ke;
    if((socket_event & SOCKET_READ) != 0 )
    {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        kevent( m_kqfd, &ke, 1, NULL, 0, NULL);
    }
    if( (socket_event & SOCKET_WRITE) != 0 )
    {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        kevent( m_kqfd, &ke, 1, NULL, 0, NULL);
    }
    return;
}

void CEventDispatch::RemoveEvent(SOCKET fd, uint8_t socket_event)
{
    struct kevent ke;
    if((socket_event & SOCKET_READ) != 0 )
    {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent( m_kqfd, &ke, 1, NULL, 0, NULL);
    }
    
    if( (socket_event & SOCKET_WRITE) != 0 )
    {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(m_kqfd, &ke, 1, NULL, 0, NULL);
    }
    return;
}

void CEventDispatch::StartDispatch(uint32_t wait_timeout)
{
    struct kevent events[1024];
    int nfds = 0;
    struct timespec timeout;
    timeout.tv_sec = 0;
    timeout.tv_nsec = wait_timeout * 1000000;
    
    if( running )
        return;
    running = true;
    while (running) {
        nfds = kevent(m_kqfd, NULL, 0, events, 1024, &timeout );
        for( int i = 0; i < nfds; ++i )
        {
            int ev_fd = events[i].ident;
            CBaseSocket *pSocket = FindBaseSocket(ev_fd);
            if( pSocket == NULL){
                continue;
            }
            if( events[i].filter == EVFILT_READ)
            {
                pSocket->OnRead();
            }
            if( events[i].filter == EVFILT_WRITE)
            {
                pSocket->OnWrite();
            }
            pSocket->ReleaseRef();
        }
        _CheckTimer();
        _CheckLoop();
    }
    return;
}

void CEventDispatch::StopDispatch()
{
    running = false;
}

#else

void CEventDispatch::AddEvent(SOCEKT fd, uint8_t socket_event)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLPRI | EPOLLERR | EPOLLHUP;
    ev.data.fd = fd;
    if( epoll_ctl( m_epfd, EPOLL_CTL_ADD, fd, &ev) != 0 )
    {
        log("epoll_ctl() failed, errno=%d", errno);
    }
}

void CEventDispatch::RemoveEvent(SOCKET fd, uint8_t socket_event)
{
    if( epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL) != 0)
    {
        log("epoll_ctl failed, errno=%d", errno);
    }
}


void CEventDispatch::StartDispatch(uint32_t wait_timeout)
{
    struct epoll_event events[1024];
    int nfds = 0;
    
    if(running)
        return;
    running = true;
    
    while (running)
    {
        nfds = epoll_wait(m_epfd, events, 1024, wait_timeout);
        for (int i = 0; i < nfds; i++)
        {
            int ev_fd = events[i].data.fd;
            CBaseSocket* pSocket = FindBaseSocket(ev_fd);
            if (!pSocket)
                continue;
            
            //Commit by zhfu @2015-02-28
#ifdef EPOLLRDHUP
            if (events[i].events & EPOLLRDHUP)
            {
                //log("On Peer Close, socket=%d, ev_fd);
                pSocket->OnClose();
            }
#endif
            // Commit End
            
            if (events[i].events & EPOLLIN)
            {
                //log("OnRead, socket=%d\n", ev_fd);
                pSocket->OnRead();
            }
            
            if (events[i].events & EPOLLOUT)
            {
                //log("OnWrite, socket=%d\n", ev_fd);
                pSocket->OnWrite();
            }
            
            if (events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP))
            {
                //log("OnClose, socket=%d\n", ev_fd);
                pSocket->OnClose();
            }
            
            pSocket->ReleaseRef();
        }
        
        _CheckTimer();
        _CheckLoop();
    }
}

void CEventDispatch::StopDispatch()
{
    running = false;
}

#endif



