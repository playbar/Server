//
//  HttpClient.cpp
//  Server
//
//  Created by mac on 16/9/2.
//  Copyright © 2016年 mac. All rights reserved.
//

#include <string>
#include "HttpClient.h"
#include "json/json.h"
#include "util.h"
using namespace std;

size_t write_data_string(void *ptr, size_t size, size_t nmemb, void *userp)
{
    size_t len = size * nmemb;
    string *response = (string*)userp;
    response->append((char*)ptr, len);
    return len;
}

size_t write_data_binary(void *ptr, size_t size, size_t nmemb, AudioMsgInfo *pAudio)
{
    size_t nLen = size * nmemb;
    if(pAudio->data_len + nLen <= pAudio->fileSize + 4 )
    {
        memcpy(pAudio->data + pAudio->data_len, ptr, nLen);
        pAudio->data_len += nLen;
    }
    return nLen;
}

CHttpClient::CHttpClient(void)
{
    
}

CHttpClient::~CHttpClient()
{
    
}

static size_t OnWriteData(void *buffer, size_t size, size_t nmemb, void *lpVoid)
{
    string *str = dynamic_cast<string*>((string *)lpVoid);
    if( NULL == str || NULL == buffer)
    {
        return -1;
    }
    char *pData = (char*)buffer;
    str->append(pData, size * nmemb );
    return nmemb;
}

CURLcode CHttpClient::Post(const string &strUrl, const string &strPost, string &strResponse)
{
    CURLcode res;
    CURL *curl = curl_easy_init();
    if( NULL == curl )
    {
        return CURLE_FAILED_INIT;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1 );
    curl_easy_setopt(curl, CURLOPT_POST, 1 );
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

CURLcode CHttpClient::Get(const string &strUrl, string &strResponse)
{
    CURLcode res;
    CURL *curl = curl_easy_init();
    if( NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1 );
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&strResponse);
    
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
    
}


