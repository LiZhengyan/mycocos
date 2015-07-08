//
//  GameScene.cpp
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#include "GameScene.h"
#include "GameCtrlLayer.h"

bool GameScene::init(){
    if(!Scene::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 添加背景
    auto sprite = Sprite::create("images/bg_game.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite);
    // 添加游戏控制层
    this->addChild(GameCtrlLayer::create());
    // 游戏层
    m_gameLayer = GameLayer::create();
    m_gameLayer->setDelegate(this);
    this->addChild(m_gameLayer);
    // 游戏结束层
    m_gameOverLayer = GameOverLayer::create();
    m_gameOverLayer->setDelegate(this);
    this->addChild(m_gameOverLayer);
    
    m_gameOverLayer->setScale(0);
    return true;
}

// GameLayerDelegate
void GameScene::gameLayerGameOver(int nowScore, int bestScore)
{
    m_gameOverLayer->gameOver(nowScore, bestScore);
    m_gameOverLayer->runAction(ScaleTo::create(0.3, 1));
}

// GameOverLayerDelegate
void GameScene::gameOverLayerRestartGame()
{
    m_gameOverLayer->runAction(ScaleTo::create(0.3, 0));
    m_gameLayer->startGame();
}
