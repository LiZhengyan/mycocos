//
//  Partic.h
//  ctaoquan1
//
//  Created by lizhengyan on 15/7/17.
//
//

#ifndef __ctaoquan1__Partic__
#define __ctaoquan1__Partic__

#include <stdio.h>
USING_NS_CC;

class Partic :public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Partic);
    Size visibleSize;
    NodeGrid* gridNodeTarget;
    
    
};

#endif /* defined(__ctaoquan1__Partic__) */
