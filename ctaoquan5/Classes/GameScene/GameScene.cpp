//
//  GameScene.cpp
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "GameCtrlLayer.h"
#include "GameOverLayer.h"
#include "GameLayer.h"
#include "cocos2d.h"

    USING_NS_CC;

bool GameScene::init()
{
    if(!Scene::init()){
        return false;
    }
    
    
    Size visibleSize  =Director::getInstance()->getVisibleSize()    ;
    
    auto sprite =Sprite::create("images/bg_game.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(sprite);
    //游戏控制层
    this->addChild(GameCtrlLayer::create());
    
    //游戏层开始
    m_gameLayer=GameLayer::create();
    m_gameLayer->setDelegate(this);
    this->addChild(m_gameLayer);
    
    //游戏结束层
    m_gameOverLayer = GameOverLayer::create();
    m_gameOverLayer->setDelegate(this);
    this->addChild(m_gameOverLayer);
    
    
    m_gameOverLayer->setScale(0);
    
 
    
    return true;
    
}

void GameScene::gameLayerGameOver(int nowScore, int bestScore)
{
    m_gameOverLayer->gameOver(nowScore, bestScore);
    m_gameOverLayer->runAction(ScaleTo::create(0.9,1));
}


void GameScene::gameOverLayerRestartGame()
{
    m_gameOverLayer->runAction(ScaleTo::create(0.3, 0));
    m_gameLayer->startGame();
    
}























