//
//  GameOverLayer.cpp
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#include "GameOverLayer.h"

bool GameOverLayer::init(){
    if(!Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 背景
    Sprite *spriteBG = Sprite::create("images/rabbitnest.png");
    spriteBG->setScale(4, 3);
    spriteBG->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(spriteBG);
    // 成绩说明
    m_labelTitle = Label::createWithSystemFont("", "", 45);
    m_labelTitle->setPosition(Point(visibleSize.width/2, visibleSize.height/2+100));
    this->addChild(m_labelTitle);
    m_labelScoreMsg = Label::createWithSystemFont("", "", 36);
    m_labelScoreMsg->setPosition(Point(visibleSize.width/2, visibleSize.height/2+20));
    this->addChild(m_labelScoreMsg);
    // 再逮一次
    Label *labelRestart = Label::createWithSystemFont("再逮一次", "", 50);
    MenuItemLabel *menuRestartLabel = MenuItemLabel::create(labelRestart, CC_CALLBACK_0(GameOverLayer::clickRestartGame,this));
    Menu* menuRestart = Menu::create(menuRestartLabel,NULL);
    menuRestart->setPosition(Point(visibleSize.width/2, visibleSize.height/2-70));
    this->addChild(menuRestart);
    
    // 不停的放大缩小
    menuRestartLabel->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.6, 0.9), ScaleTo::create(1.4, 1.1), NULL)));
    return true;
}

void GameOverLayer::gameOver(int nowScore, int bestScore)
{
    if (bestScore > 0) {
        if (nowScore > bestScore) {
            m_labelTitle->setString("您破纪录了");
            m_labelTitle->runAction(Blink::create(1, 8));
        }
        else {
            m_labelTitle->setString("您未破纪录");
            m_labelTitle->runAction(Blink::create(1, 4));
        }
        m_labelScoreMsg->setString(StringUtils::format("您的历史纪录是%d只", bestScore));
    }
    else {
        if (nowScore > 0) {
            m_labelTitle->setString("您有新成绩了");
            m_labelTitle->runAction(Blink::create(1, 8));
            m_labelScoreMsg->setString(StringUtils::format("这次逮到了%d只", nowScore));
        }
        else {
            m_labelTitle->setString("您点错了");
            m_labelTitle->runAction(Blink::create(1, 8));
            m_labelScoreMsg->setString("这次一只兔子也没逮到");
        }
    }
}

void GameOverLayer::clickRestartGame()
{
    m_delegate->gameOverLayerRestartGame();
}
