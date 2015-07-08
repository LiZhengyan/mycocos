//
//  GameLayer.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/30.
//
//

#ifndef __ctaoquan5__GameLayer__
#define __ctaoquan5__GameLayer__

#include "cocos2d.h"
#include "RabbitMatrix.h"
USING_NS_CC;

class GameLayerDelegate
{
    public:
        virtual void gameLayerGameOver(int nowScore,int bestScore)=0;

    
};


class GameLayer :public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameLayer);
    virtual bool onTouchBegan(Touch* touch,Event* event);
    
    void setDelegate(GameLayerDelegate * delegate){m_delegate = delegate;}
    
    void startGame();
    
private:
    void gameOver();
    
    GameLayerDelegate* m_delegate;
    Label* m_labelHighScore;
    Label* m_labelLevel;
    bool m_gameRun;
    
    RabbitMatrix* m_rabbitMatrix;
};




#endif /* defined(__ctaoquan5__GameLayer__) */
