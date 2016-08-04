/*
 *  Server.cpp
 *  Server
 *
 *  Created by mac on 16/8/4.
 *  Copyright © 2016年 mac. All rights reserved.
 *
 */

#include <iostream>
#include "base.hpp"
#include "ServerPriv.hpp"

void Server::HelloWorld(const char * s)
{
	 ServerPriv *theObj = new ServerPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void ServerPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

