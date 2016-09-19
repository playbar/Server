//
//  HttpConn.hpp
//  Server
//
//  Created by mac on 16/9/19.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __HTTP_CONN_H__
#define __HTTP_CONN_H__

#include <stdio.h>
#include "netlib.h"
#include "util.h"
#include "HttpParserWrapper.h"

#define HTTP_CONN_TIMEOUT       60000
#define READ_BUF_SIZE           2048
#define HTTP_RESPONSE_HTML      "HTTP/1.1 200 OK\r\n"\
                                "Connection:close\r\n"\
                                "Content-Length:%d\r\n"\
                                "Content-Type:text/html;charset=utf-8\r\n\r\n%s"

#define HTTP_RESPONSE_HTML_MAX  1024

enum{
    CONN_STATE_IDLE,
    CONN_STATE_CONNECTED,
    CONN_STATE_OPEN,
    CONN_STATE_CLOSED,
};

class CHttpConn : public CRefObject
{
    
};


#endif /* HttpConn_hpp */
