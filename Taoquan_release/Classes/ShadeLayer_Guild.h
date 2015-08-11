//
//  ShadeLayer_Guild.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/23.
//
//

#ifndef __TaoQuan__ShadeLayer_Guild__
#define __TaoQuan__ShadeLayer_Guild__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ShadeLayer_Guild : public Layer {
    
public:
    
    virtual bool init();
    
    CREATE_FUNC(ShadeLayer_Guild);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void menuNextCallback(Ref* pSender);//下一关按钮回调
    void menuThisLevelCallback(Ref* pSender);//本关金星模式按钮回调
    void menuResatrtCallback(Ref* pSender);//重新开始按钮回调
    Size visibleSize;
    
    //int currentLevel;
    Vector<Sprite*>starVector;
    int _level;
};

#endif /* defined(__TaoQuan__ShadeLayer_Guild__) */