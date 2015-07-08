//
//  GameCtrlLayer.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#ifndef __ctaoquan5__GameCtrlLayer__
#define __ctaoquan5__GameCtrlLayer__

#include "cocos2d.h"
USING_NS_CC;


class GameCtrlLayer:public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameCtrlLayer);
    
private:
    
    void clickBacktoMenu();
    
    
    
};

#endif /* defined(__ctaoquan5__GameCtrlLayer__) */
