//
//  Userguide.h
//  Taoquan_release
//
//  Created by lizhengyan on 15/8/10.
//
//

#ifndef __Taoquan_release__Userguide__
#define __Taoquan_release__Userguide__

#include <stdio.h>
#include "cocos2d.h"
#include "ResolvePicture.h"
#include "ShadeLayer.h"
#include "FailedShadeLayer.h"
#include "PauseLayer.h"

USING_NS_CC;



class Userguide :public Layer
{
public:
    static Scene* createScene();
    CREATE_FUNC(Userguide)
    virtual bool init();
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    void Touch_first();
    void Touch_second();
    void Touch_three();
    void Touch_four();
    void Touch_five();
    void Touch_six();
    
    Sprite* _spriteQuan;
    
    
    bool isTouch;
    Sprite* w1;
    Sprite* w2;
    Sprite* w3;
    Sprite* w4;
    Sprite* w5;
    Sprite* z1;
    Sprite* z2;
    Sprite* z3;
    Sprite* z4;
    
    Size visibleSize;
    Vec2 origin;
    
    Sprite* mubiao; // 被套物体的坐标
    Sprite* tz_zhezhao;
    Sprite* tz_wz;
    
    bool sprite_xxoo=false;
    

    RepeatForever* repeatPG;
    Speed* _progressTimerSpeed;//进度条速度
    
    Sprite* _spriteTiao;
    ProgressTimer* _powerProgress;
    
    void updateTime(float dt);
    
    
    void menuPauseCallback(Ref* pSender);
    void enterIntoSucceedUI();
    void spriteVectorMove();
    
private:
    Vector<ResolvePicture*> spriteVector;//小图
    Vector<ResolvePicture*> hiddenPictureVector;//隐藏的小图
    Vector<ResolvePicture*> showPictureVector;//隐藏的小图
    Sprite* _wholePicture;//全图
    
    
    
};

#endif /* defined(__Taoquan_release__Userguide__) */
