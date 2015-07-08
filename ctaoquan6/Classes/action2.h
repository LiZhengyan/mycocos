//
//  action2.h
//  ctaoquan6
//
//  Created by lizhengyan on 15/6/24.
//
//

#ifndef __ctaoquan6__action2__
#define __ctaoquan6__action2__

#include "cocos2d.h"


class Action2 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Action2);
};


#endif /* defined(__ctaoquan6__action2__) */
