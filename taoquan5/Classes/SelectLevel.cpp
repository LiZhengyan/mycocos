//
//  SelectLevel.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "SelectLevel.h"
#include "GameScene.h"
USING_NS_CC;
Scene* SelectLevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectLevel::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    this->addChild(label, 1);
    
    auto sprite = Sprite::create("selectlevel/BG.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    for (int i=0; i<3; i++) {
        for (int j=1; j<4; j++) {
            char name[20];
            sprintf(name, "selectlevel/%d.png",i*3+j);
            auto levelButton = MenuItemImage::create(name,name,CC_CALLBACK_1(SelectLevel::menuCloseCallback, this));
            levelButton->setPosition(Vec2(116+50+158*(j-1),876-(levelButton->getContentSize().height+42)*i-levelButton->getContentSize().height/2));
            
            auto menu = Menu::create(levelButton, NULL);
            menu->setPosition(Vec2::ZERO);
            this->addChild(menu, 2);
        }

    }
        
    return true;
}
                    
void SelectLevel::menuCloseCallback(Ref* pSender)
{
//    Director::getInstance()->end();
//            
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//            exit(0);
//#endif
    auto gameScene=GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);

}

