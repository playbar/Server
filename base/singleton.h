//
//  singleton.h
//  Server
//
//  Created by mac on 16/9/18.
//  Copyright © 2016年 mac. All rights reserved.
//

#ifndef BASE_SINGLETON_H_
#define BASE_SINGLETON_H_

template <typename T>
class Singleton {
public:
    static T& Instance()
    {
        if( Singleton::s_instance == NULL)
        {
            Singleton::s_instance = CreateInstance();
        }
        return *(Singleton::s_instance);
    }
    
    static T* GetInstance()
    {
        if( Singleton::s_instance == NULL)
        {
            Singleton::s_instance = CreateInstance();
        }
        return Singleton::s_instance;
    }
    
    static T* getInstance()
    {
        if( Singleton::s_instance == NULL)
        {
            Singleton::s_instance = CreateInstance();
        }
        return Singleton::s_instance;
    }
    
    static void Destroy()
    {
        if( Singleton::s_instance != NULL)
        {
            DestroyInstance(Singleton::s_instance);
            Singleton::s_instance = NULL;
        }
    }
    
    
public:
    
private:
    static T *CreateInstance()
    {
        return new T();
    }
    
    static void DestroyInstance(T *p)
    {
        delete p;
    }
    
private:
    static T *s_instance;
    
private:
    explicit Singleton(Singleton const &);
    Singleton &operator=(Singleton const &){return *this;}
    
};

template <typename T>
T *Singleton<T>::s_instance = NULL;

#endif /* singleton_h */
