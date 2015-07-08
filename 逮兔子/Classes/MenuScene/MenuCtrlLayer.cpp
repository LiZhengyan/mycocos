//
//  MenuCtrlLayer.cpp
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#include "MenuCtrlLayer.h"
#include "GameScene.h"

bool MenuCtrlLayer::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 开始游戏按钮
    Label *labelStart = Label::createWithSystemFont("开始游戏", "", 70);
    MenuItemLabel *menuItemLabel = MenuItemLabel::create(labelStart, CC_CALLBACK_0(MenuCtrlLayer::clickStartGame,this));
    Menu* menuStart = Menu::create(menuItemLabel,NULL);
    menuStart->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(menuStart);
    
    // 按钮不停的放大缩小
    menuItemLabel->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5, 0.8), ScaleTo::create(0.5, 1.2), NULL)));
    
    return true;
}

void MenuCtrlLayer::clickStartGame()
{
    Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, GameScene::create()));
}
