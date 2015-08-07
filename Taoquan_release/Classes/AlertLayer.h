//
//  AlertLayer.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/14.
//
//

#ifndef __TaoQuan2__AlertLayer__
#define __TaoQuan2__AlertLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class AlertLayer:public Layer{
public:
    virtual bool init();
    
    static AlertLayer* create();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void menuConfirmCallback(Ref* pSender);
    void menuCancelCallback(Ref* pSender);
};
#endif /* defined(__TaoQuan2__AlertLayer__) */
