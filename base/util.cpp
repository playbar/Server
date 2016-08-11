//
//  util.cpp
//  Server
//
//  Created by mac on 16/8/11.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "util.h"
#include "sstream"
using namespace std;

CRefObject::CRefObject(){
    m_lock = NULL;
    m_refCount = 1;
}

CRefObject::~CRefObject()
{
    
}

void CRefObject::AddRef()
{
    if( m_lock){
        m_lock->lock();
        ++m_refCount;
        m_lock->unlock();
    }
    else{
        ++m_refCount;
    }
}

void CRefObject::ReleaseRef()
{
    if( m_lock ){
        m_lock->lock();
        --m_refCount;
        if( m_refCount == 0 ){
            m_lock->unlock();
            delete this;
            return;
        }
        m_lock->unlock();
    }else{
        --m_refCount;
        if( 0 == m_refCount ){
            delete  this;
        }
    }
}

uint64_t get_tick_count(){
    struct timeval tval;
    uint64_t ret_tick;
    
    gettimeofday(&tval, NULL);
    
    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
}

void util_sleep( uint32_t millisecond){
    usleep( millisecond * 1000);
}

CStrExplode::CStrExplode(char *str, char seperator){
    m_item_cnt = 1;
    char *pos = str;
    while( *pos ){
        if( *pos == seperator){
            m_item_cnt++;
        }
        ++pos;
    }
    
    m_item_list = new char*[m_item_cnt];
    int idx = 0;
    char *start = pos = str;
    while( *pos ){
        if( pos != start && *pos == seperator ){
            uint32_t len = pos - start;
            m_item_list[idx] = new char[len+1];
            strncpy( m_item_list[idx], start, len );
            m_item_list[idx][len] = '\0';
            ++idx;
            start = pos + 1;
        }
        ++pos;
    }
    
    uint32_t len = pos - start;
    if( len != 0 ){
        m_item_list[idx] = new char[len+1];
        strncpy( m_item_list[idx], start, len );
        m_item_list[idx][len] = '\0';
    }
    return;
    
}

CStrExplode::~CStrExplode(){
    for( uint32_t i = 0; i < m_item_cnt; ++i ){
        delete [] m_item_list[i];
    }
    delete [] m_item_list;
}

char *replaceStr( char *pSrc, char oldChar, char newChar ){
    if( NULL == pSrc ){
        return NULL;
    }
    
    char *pHead = pSrc;
    while( *pHead != '\0'){
        if( *pHead == oldChar ){
            *pHead = newChar;
        }
        ++pHead;
    }
    return pSrc;
}


