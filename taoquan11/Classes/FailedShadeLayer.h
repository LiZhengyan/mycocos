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
    Sprite* _propNotEnoughBG;
    MenuItemImage* _yesButton;
    MenuItemImage* _noButton;
    Menu* _menu;
    
    bool _isFile;//判断本关是否存档
    
    void alertPropNotEnoughFunction();//弹出警告框
    void menupropNotEnoughCallback(Ref*pSender);
};


#endif /* defined(__TaoQuan2__FailedShadeLayer__) */
