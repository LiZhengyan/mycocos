//
//  MenuCtrlLayer.cpp
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#include "MenuCtrlLayer.h"
#include "GameScene.h"

bool MenuCtrlLayer::init()
{
    if(!Layer::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    Label* labelStart = Label::createWithSystemFont("开始游戏", "",50);
    MenuItemLabel* menuItemLabel =MenuItemLabel::create(labelStart, CC_CALLBACK_0(
                                            MenuCtrlLayer::clickstartGame,this));
    
    Menu* menuStart=Menu::create(menuItemLabel, NULL);
    menuStart->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(menuStart);
    auto menuaction=RepeatForever::create(Sequence::create(ScaleTo::create(0.5,0.8),ScaleTo::create(0.5, 1.2),NULL));
    
    menuItemLabel->runAction(menuaction);
    
    return true;
    
}

void MenuCtrlLayer::clickstartGame()
{
    Director::getInstance()->replaceScene(TransitionSplitCols::create(1,  GameScene::create()));
}