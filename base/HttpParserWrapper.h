//
//  HttpParserWrapper.hpp
//  Server
//
//  Created by mac on 16/9/6.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef http_msg_server_HttpParserWrapper_h
#define http_msg_server_HttpParserWrapper_h

#include <stdio.h>
#include "util.h"
#include "http_parser.h"

class CHttpParserWrapper
{
public:
    CHttpParserWrapper();
    virtual ~CHttpParserWrapper(){}
    
private:
    http_parser m_http_parser;
    http_parser_settings m_settings;
    
    bool m_read_all;
    bool m_read_referer;
    bool m_read_forward_ip;
    bool m_read_user_agent;
    bool m_read_content_type;
    bool m_read_content_len;
    bool m_read_host;
    uint32_t m_total_length;
    string m_url;
    string m_body_content;
    string m_referer;
    string m_forward_ip;
    string m_user_agent;
    string m_content_type;
    uint32_t m_content_len;
    string m_host;
};

#endif /* HttpParserWrapper_hpp */
