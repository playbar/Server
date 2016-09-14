//
//  imconn.cpp
//  Server
//
//  Created by mac on 16/9/7.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "imconn.h"

static CImConn *FindImConn(ConnMap_t *imconn_map, net_handle_t handle)
{
    CImConn *pConn = NULL;
    ConnMap_t::iterator iter = imconn_map->find(handle);
    if( iter != imconn_map->end())
    {
        pConn = iter->second;
        pConn->AddRef();
    }
    return pConn;
}
