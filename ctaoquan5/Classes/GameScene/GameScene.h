//
//  GameScene.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/29.
//
//

#ifndef __ctaoquan5__GameScene__
#define __ctaoquan5__GameScene__

#include "cocos2d.h"
#include "GameLayer.h"
#include "GameOverLayer.h"


USING_NS_CC;

class GameScene : public cocos2d::Scene,public GameLayerDelegate,public GameOverLayerDelegate
{
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    
public:
    virtual void gameLayerGameOver(int nowScore ,int bestScore);
    virtual void gameOverLayerRestartGame();
private:
    GameOverLayer* m_gameOverLayer;
    GameLayer* m_gameLayer;
    
    

};


#endif /* defined(__ctaoquan5__GameScene__) */
