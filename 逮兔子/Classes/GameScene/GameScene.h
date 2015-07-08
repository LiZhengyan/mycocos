//
//  GameScene.h
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#ifndef __FindRabbit__GameScene__
#define __FindRabbit__GameScene__

#include <stdio.h>
#include "GameLayer.h"
#include "GameOverLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene, public GameLayerDelegate, public GameOverLayerDelegate
{
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    
public:
    // GameLayerDelegate
    virtual void gameLayerGameOver(int nowScore, int bestScore);
    // GameOverLayerDelegate
    virtual void gameOverLayerRestartGame();
    
private:
    GameLayer *m_gameLayer;
    GameOverLayer *m_gameOverLayer;
};

#endif /* defined(__FindRabbit__GameScene__) */
