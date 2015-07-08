//
//  GameCtrlLayer.cpp
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#include "GameCtrlLayer.h"
#include "GameScene.h"
#include "MenuScene.h"

bool GameCtrlLayer::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize =Director::getInstance()->getVisibleSize();
    
    Label* labelBack = Label::createWithSystemFont("返回", "",50);
    MenuItemLabel* menuItemLabel =MenuItemLabel::create(labelBack, CC_CALLBACK_0(
                                                                                  GameCtrlLayer::clickBacktoMenu,this));
    
    Menu* menuBack=Menu::create(menuItemLabel, NULL);
    menuBack->setPosition(Vec2(80,visibleSize.height-50));
    
    this->addChild(menuBack);

    
    
    
    return true;
}


void GameCtrlLayer::clickBacktoMenu()
{
    Director::getInstance()->replaceScene(TransitionSplitCols::create(1,  MenuScene::create()));
}