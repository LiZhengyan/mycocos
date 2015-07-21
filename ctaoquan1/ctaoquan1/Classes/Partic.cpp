//
//  Partic.cpp
//  ctaoquan1
//
//  Created by lizhengyan on 15/7/17.
//
//

#include "Partic.h"



Scene* Partic::createScene()
{
    auto scene = Scene::create();
    auto layer = Partic::create();
    scene->addChild(layer);
    return scene;
}


bool Partic::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    visibleSize=Director::getInstance()->getVisibleSize();
    auto origin=Director::getInstance()->getVisibleOrigin();
    Sprite* bgPic=Sprite::create("gamescene/gameBG1.png");
    log("x=%f,y=%f",visibleSize.width,visibleSize.height);
    bgPic->setPosition(Vec2(origin.x +visibleSize.width/2,origin.y + visibleSize.height/2));
    bgPic->setScale(visibleSize.width/700);
//    addChild(bgPic,0);
    
    auto _grossini=Sprite::create("5.png");
    _grossini->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(_grossini);
    
    Animation* hua_an=Animation::create();
    for (int i=0; i<=33; i++) {
        char fname[100]={0};
        sprintf(fname, "hua/hua_000%02d.png",i);
        log("%s",fname);
        hua_an->addSpriteFrameWithFile(fname);
    }
    hua_an->setDelayPerUnit(1.8f / 33.0f);
    hua_an->setRestoreOriginalFrame(true);
    
    auto action = Animate::create(hua_an);
    
    
    
    
    Animation* wave_an=Animation::create();
    for (int i=1; i<=5; i++) {
        char fname[100]={0};
        sprintf(fname, "shuibo/%d.png",i);
        log("%s",fname);
        wave_an->addSpriteFrameWithFile(fname);
    }
    wave_an->setDelayPerUnit(1.0f / 4.0f);
    wave_an->setRestoreOriginalFrame(true);
    auto wave_action = Animate::create(wave_an);
    
    
    _grossini->runAction(RepeatForever::create(Sequence::create(wave_action,wave_action->reverse() ,NULL)));
    addChild(_grossini,3);
    
    
    CCActionInterval* waves = CCWaves::create(50, CCSize(100, 100), 100, 40, true, true);
    auto new_lens=Lens3D::create(10,Size(100, 100),_grossini->getPosition(),40 );
    
    auto new_ripp=Liquid::create(50,Size(100, 100),20,10);
//     Ripple3D::create(时间,网格大小,坐标,半径,速度,振幅);  
    auto gridNodeTarget=NodeGrid::create();
    addChild(gridNodeTarget,1);
    gridNodeTarget->addChild(bgPic);
//    gridNodeTarget->runAction(new_ripp);
    return true;
    
}
