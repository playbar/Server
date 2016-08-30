//
//  Condition.hpp
//  Server
//
//  Created by mac on 16/8/30.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <stdio.h>
#include <pthread.h>
#include "Lock.h"

class CCondition
{
public:
    CCondition(CLock *pLock);
    ~CCondition();
    void wait();
    
    bool waitTime( uint64_t nWaitTime);
    void notify();
    void notifyAll();
    
private:
    CLock *m_pLock;
    pthread_cond_t m_cond;
    
};

#endif /* Condition_h */
