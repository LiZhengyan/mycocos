//
//  MenuCtrlLayer.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#ifndef __ctaoquan5__MenuCtrlLayer__
#define __ctaoquan5__MenuCtrlLayer__

USING_NS_CC;

class MenuCtrlLayer:public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MenuCtrlLayer);
    
private:
    void clickstartGame();
    
};

#endif /* defined(__ctaoquan5__MenuCtrlLayer__) */
