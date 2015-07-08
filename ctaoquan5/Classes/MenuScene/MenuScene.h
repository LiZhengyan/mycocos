//
//  MenuScene.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#ifndef __ctaoquan5__MenuScene__
#define __ctaoquan5__MenuScene__

#include "cocos2d.h"
USING_NS_CC;

class MenuScene : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* defined(__ctaoquan5__MenuScene__) */
