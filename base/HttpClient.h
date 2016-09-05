//
//  HttpClient.hpp
//  Server
//
//  Created by mac on 16/9/2.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __HTTP_CURL_H__
#define __HTTP_CURL_H__

#include <stdio.h>
#include <curl/curl.h>
#include "public_define.h"

class CHttpClient
{
public:
    CHttpClient(void);
    ~CHttpClient(void);
    
public:
    CURLcode Post( const string &strUrl, const string &strPost, string &strResponse);
    CURLcode Get(const string &strUrl, string &strResponse);
    string UploadByteFile(const string &url, void *data, int data_len);
    bool DownloadByteFile(const string &url, AudioMsgInfo *pAudioMsg);
    
    
};

#endif /* HttpClient_h */
