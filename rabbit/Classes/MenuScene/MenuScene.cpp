//
//  MenuScene.cpp
//  FindRabbit
//
//  Created by yangjh on 15/4/22.
//
//

#include "MenuScene.h"
#include "MenuCtrlLayer.h"

bool MenuScene::init(){
    if(!Scene::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 添加背景
    auto sprite = Sprite::create("images/bg_game.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite);
    // 添加控制层
    this->addChild(MenuCtrlLayer::create());
    
    return true;
}
