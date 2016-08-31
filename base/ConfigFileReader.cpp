//
//  ConfigFileReader.cpp
//  Server
//
//  Created by mac on 16/8/31.
//  Copyright © 2016年 mac. All rights reserved.
//

#include "ConfigFileReader.h"

CConfigFileReader::CConfigFileReader(const char *filename)
{
    _LoadFile(filename);
}

CConfigFileReader::~CConfigFileReader()
{
    
}

char *CConfigFileReader::GetConfigName(const char *name)
{
    if( !m_load_ok){
        return NULL;
    }
    char *value = NULL;
    map<string, string>::iterator it = m_config_map.find(name);
    if( it != m_config_map.end() )
    {
        value = (char*)it->second.c_str();
    }
    return value;
}


