//
//  RouteServConn.hpp
//  Server
//
//  Created by mac on 16/9/22.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef ROUTESERVCONN_H_
#define ROUTESERVCONN_H_

#include <stdio.h>
#include "imconn.h"
#include "ServInfo.h"

class CRouteServConn : public CImConn
{
public:
    CRouteServConn();
    virtual ~CRouteServConn();
    
    bool IsOpen() { return m_bOpen;}
    uint64_t GetConnectTime(){ return m_connect_time;}
    
    void Connect(const char *server_ip, uint16_t server_port, uint32_t serv_idx);
    
    virtual void Close();
    virtual void OnConfirm();
    virtual void onClose();
    virtual void OnTimer(uint64_t curr_tick);
    
    virtual void HandlePdu(CImPdu *pPdu);
    
private:
    void _HandleKickUser( CImPdu *pPdu);
    void _HandleStatusNotify(CImPdu *pPdu);
    void _HandleMsgREadNotify(CImPdu *pPdu);
    void _HandleMsgData(CImPdu *pPdu);
    void _HandleP2Msg(CImPdu *pPdu);
    void _HandleUsersStatusResponse(CImPdu *pPdu);
    void _HandlePCLoginStatusNotify(CImPdu *pPdu);
    void _HandleRemoveSessionNotify(CImPdu *pPdu);
    void _HandleSignInfoChangedNotify(CImPdu *pPdu);
    
private:
    bool        m_bOpen;
    uint32_t    m_serv_idx;
    uint32_t    m_connect_time;
};

#endif /* RouteServConn_hpp */
