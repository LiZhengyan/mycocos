//
//  ShadeLayer.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/23.
//
//

#ifndef __TaoQuan__ShadeLayer__
#define __TaoQuan__ShadeLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ShadeLayer : public Layer {
    
public:
    
    virtual bool init();
    
    static ShadeLayer* create();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void menuNextCallback(Ref* pSender);//下一关按钮回调
    
    
    Size visibleSize;
    
    //int currentLevel;
    Vector<Sprite*>starVector;
    int _level;
};

#endif /* defined(__TaoQuan__ShadeLayer__) */
