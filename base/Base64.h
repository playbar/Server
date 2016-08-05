//
//  Base64.hpp
//  Server
//
//  Created by mac on 16/8/4.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __Base64_h__
#define __Base64_h__

#include <stdio.h>
#include <iostream>
using namespace std;

string base64_decode(const string &ascdata);
string base64_encode(const string &bindata);

#endif /* Base64_hpp */
