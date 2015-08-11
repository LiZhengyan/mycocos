//
//  GameCtrlLayer.cpp
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#include "GameCtrlLayer.h"
#include "MenuScene.h"

bool GameCtrlLayer::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 返回按钮
    Label *labelBack = Label::createWithSystemFont("返回", "", 40);
    MenuItemLabel *menuItemLabel = MenuItemLabel::create(labelBack, CC_CALLBACK_0(GameCtrlLayer::clickBackToMenu,this));
    Menu* menuBack = Menu::create(menuItemLabel,NULL);
    menuBack->setPosition(80,visibleSize.height-50);
    this->addChild(menuBack);
    
    // 按钮不停的放大缩小
    menuItemLabel->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5, 0.8), ScaleTo::create(0.5, 1.2), NULL)));
    
    return true;
}

void GameCtrlLayer::clickBackToMenu()
{
    Director::getInstance()->replaceScene(TransitionSplitCols::create(0.3f, MenuScene::create()));
}
