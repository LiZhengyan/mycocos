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
    
    Size visibleSize;
    
};


#endif /* defined(__TaoQuan2__FailedShadeLayer__) */
