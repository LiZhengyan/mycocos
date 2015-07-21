//
//  PauseLayer.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/3.
//
//

#ifndef __TaoQuan2__PauseLayer__
#define __TaoQuan2__PauseLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class PauseLayer:public Layer{
public:
    virtual bool init();
    
    static PauseLayer* create();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void menuSelectLevelCallback(Ref* pSender);
    void menuResumeCallback(Ref* pSender);
};

#endif /* defined(__TaoQuan2__PauseLayer__) */
