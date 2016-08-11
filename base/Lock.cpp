//
//  Lock.cpp
//  Server
//
//  Created by mac on 16/8/11.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "Lock.h"

CLock::CLock(){
    pthread_mutex_init(&m_lock, NULL );
}
