//
//  LogoScene.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/15.
//
//

#include "LogoScene.h"
#include "LoadScene.h"
USING_NS_CC;
Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto spriteBG = Sprite::create("background.jpg");
    
    spriteBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    spriteBG->setScale(visibleSize.width/spriteBG->getContentSize().width,visibleSize.height/spriteBG->getContentSize().height);

    this->addChild(spriteBG, 0);
    auto logoSp = Sprite::create("logo.png");
    logoSp->setScale(visibleSize.width*0.9/640);
    logoSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.6 + origin.y));
    
    this->addChild(logoSp, 2);
    
    this->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        //跳转到选择关卡界面
        Scene* loadScene=LoadScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.2f, loadScene));
    }),NULL));
    
    
    

    return true;
}
