//
//  Task.h
//  Server
//
//  Created by mac on 16/9/18.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef __TASK_H__
#define __TASK_H__

class CTask
{
public:
    CTask(){}
    virtual ~CTask(){};
    virtual void run() = 0;
private:
};


#endif /* Task_h */

