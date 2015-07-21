//
//  FailedShadeLayer.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/6/30.
//
//

#ifndef __TaoQuan2__FailedShadeLayer__
#define __TaoQuan2__FailedShadeLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class FailedShadeLayer : public Layer {
    
public:
    
    virtual bool init();
    
    static FailedShadeLayer* create();
    
    void menuRestartCallback(Ref* pSender);
    void menuSelectLevelCallback(Ref* pSender);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    Size visibleSize;
    
    bool _isFile;//判断本关是否存档
    int _clevel;
    
};


#endif /* defined(__TaoQuan2__FailedShadeLayer__) */
