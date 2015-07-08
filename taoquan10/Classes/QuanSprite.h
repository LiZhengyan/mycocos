//
//  QuanSprite.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/3.
//
//

#ifndef __TaoQuan2__QuanSprite__
#define __TaoQuan2__QuanSprite__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class QuanSprite:public Sprite {
    
public:
    static QuanSprite* createSprite();
    void initQuanSprite(Vec2 p);
    
    void quanRunActionBlink();
    void quanRunMoveToPoint(float time,Vec2 p);
    
};

#endif /* defined(__TaoQuan2__QuanSprite__) */
