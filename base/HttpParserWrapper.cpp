//
//  HttpParserWrapper.cpp
//  Server
//
//  Created by mac on 16/9/6.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "HttpParserWrapper.h"

#define MAX_REFERER_LEN 32

CHttpParserWrapper::CHttpParserWrapper()
{
    
}

void CHttpParserWrapper::ParserHttpContent(const char *buf, uint32_t len)
{
    http_parser_init(&m_http_parser, HTTP_REQUEST);
    memset( &m_settings, 0, sizeof( m_settings));
    m_settings.on_url = OnUrl;
    m_settings.on_header_field = OnHeaderField;
    m_settings.on_header_value = OnHeaderValue;
    m_settings.on_headers_complete = OnHeadersComplete;
    m_settings.on_body = OnBody;
    m_settings.on_message_complete = OnMessageComplete;
    m_settings.object = this;
    
    m_read_all = false;
    m_read_referer = false;
    m_read_forward_ip = false;
    m_read_user_agent = false;
    m_read_content_type = false;
    m_read_content_len = false;
    m_read_host = false;
    m_total_length = 0;
    m_url.clear();
    m_body_content.clear();
    m_referer.clear();
    m_forward_ip.clear();
    m_user_agent.clear();
    m_content_type.clear();
    m_content_len = 0;
    m_host.clear();
    
    http_parser_execute(&m_http_parser, &m_settings, buf, len);
    return;
    
}
