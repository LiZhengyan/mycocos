//
//  LogoScene.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/15.
//
//

#ifndef __TaoQuan2__LogoScene__
#define __TaoQuan2__LogoScene__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class LogoScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
    
};
#endif /* defined(__TaoQuan2__LogoScene__) */
