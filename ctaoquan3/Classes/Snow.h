//
//  Snow.h
//  ctaoquan3
//
//  Created by lizhengyan on 15/7/6.
//
//

#ifndef __ctaoquan3__Snow__
#define __ctaoquan3__Snow__

#include <stdio.h>

class Snow  : public cocos2d::Layer
{
    cocos2d::__Array * list;
public:
    ~Snow();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Snow);
    
private:
    void clickstartGame(Ref * pSender);
};

#endif /* defined(__ctaoquan3__Snow__) */
