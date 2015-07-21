//
//  Tuowei.h
//  mytest5
//
//  Created by lizhengyan on 15/7/17.
//
//

#ifndef __mytest5__Tuowei__
#define __mytest5__Tuowei__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Tuowei :public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Tuowei);
    void update(float dt);
    cocos2d::__Array* bulltArr;
    cocos2d::__Array* streakArr;
    cocos2d::Size size;
    
private:
    
    bool TouchBegan(Touch *pTouch, Event *pEvent);
    void TouchMoved(Touch *pTouch, Event *pEvent);
    void TouchEnded(Touch *pTouch, Event *pEvent);
    void createBullt(Point startPoint);
    ~Tuowei();
    void onEnter();
    void onExit();
};


#endif /* defined(__mytest5__Tuowei__) */
