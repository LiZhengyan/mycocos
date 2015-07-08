//
//  QuanSprite.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/3.
//
//

#include "QuanSprite.h"
QuanSprite* QuanSprite::createSprite()
{
    QuanSprite* quan = new QuanSprite();
    if (quan)
    {
        return quan;
    }
    return NULL;
}


void QuanSprite::initQuanSprite(Vec2 p)
{
    
    this->initWithFile("gamescene/quan.png");
    this->setPosition(p);
    
}

void QuanSprite::quanRunActionBlink()
{
    Blink* menuItemBlink=Blink::create(1.0f, 2);
    this->runAction(menuItemBlink);
}
void QuanSprite::quanRunMoveToPoint(float time,Vec2 p)
{
    MoveTo* quanMove=MoveTo::create(time,p);
    auto ease=EaseSineOut::create(quanMove);
    this->runAction(ease);
}
