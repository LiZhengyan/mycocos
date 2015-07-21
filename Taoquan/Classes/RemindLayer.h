//
//  RemindLayer.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/17.
//
//

#ifndef __TaoQuan2__RemindLayer__
#define __TaoQuan2__RemindLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class RemindLayer:public Layer{
public:
    virtual bool init();
    
    static RemindLayer* create();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    void menuConfirmCallback(Ref* pSender);
    void menuCancelCallback(Ref* pSender);
};
#endif /* defined(__TaoQuan2__RemindLayer__) */
