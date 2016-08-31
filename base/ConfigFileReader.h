//
//  ConfigFileReader.hpp
//  Server
//
//  Created by mac on 16/8/31.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef CONFIGFILEREADER_H_
#define CONFIGFILEREADER_H_

#include <stdio.h>
#include "util.h"

class CConfigFileReader
{
public:
    CConfigFileReader(const char *filename);
    ~CConfigFileReader();
    
    char *GetConfigName( const char *name);
    int SetConfigValue( const char *name, const char *value );
    
private:
    void _LoadFile( const char *filename);
    int _WriteFile( const char *filename = NULL);
    void _ParseLine(char *line);
    char *_TrimSpace(char *name);
    
    bool m_load_ok;
    map<string, string> m_config_map;
    string m_config_file;
    
};


#endif /* ConfigFileReader_hpp */
