//
//  file_server_util.h
//  Server
//
//  Created by mac on 16/9/29.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __FILE_SERVER_UTIL_H__
#define __FILE_SERVER_UTIL_H__

#include <pthread.h>
#include <uuid/uuid.h>

#include "imconn.h"

typedef struct file_header_t{
    char task_id[128];
    char from_user_id[64];
    char to_user_id[64];
    char create_time[128];
    char file_name[512];
    char file_size[64];
    char file_type[64];
    
    file_header_t () {
        memset(task_id, 0, 128);
        memset(from_user_id, 0, 64);
        memset(to_user_id, 0, 64);
        memset(create_time, 0, 64);
        memset(file_name, 0, 512);
        memset(file_size, 0, 64);
        memset(file_type, 0, 64);
    }
    
    void set_task_id(const char *p)
    {
        strncpy(task_id, p, 128 < strlen(p) ? 128 : strlen(p));
    }
    
    void set_from_user_id(const char *p)
    {
        size_t ilen = strlen(p);
        strncpy(task_id, p, 128 < ilen ? 128 :ilen);
    }
    
    void set_from_user_id( uint32_t id)
    {
        strcpy( from_user_id, idtourl(id));
    }
    
    void set_to_user_id(const char *p)
    {
        size_t ilen = strlen(p);
        strncpy(to_user_id, p, 64 < ilen ? 64 : ilen);
    }
    
    void set_to_user_id(uint32_t id)
    {
        strcpy(to_user_id, idtourl(id));
    }
    
    void set_create_time(time_t t)
    {
        sprintf(create_time, "%ld", t);
    }
    
    void set_file_name(const char* p)
    {
        size_t ilen = strlen(p);
        sprintf(file_name, p, 512 < ilen ? 512 : ilen);
    }
    
    void set_file_size(uint32_t size)
    {
        sprintf(file_size, "%d", size);
    }
    
}file_header;

#endif /* file_server_util_h */
