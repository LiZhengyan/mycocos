//
//  HelloNet.h
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/9.
//
//

#ifndef __ctaoquan7__HelloNet__
#define __ctaoquan7__HelloNet__

#include <stdio.h>
#include "curl/curl.h"

#define BASE_URL "baidu.com"

USING_NS_CC;

class HelloNet: public cocos2d::Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    
};




#endif /* defined(__ctaoquan7__HelloNet__) */
