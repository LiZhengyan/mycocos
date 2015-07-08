//
//  GameOverLayer.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/30.
//
//

#ifndef __ctaoquan5__GameOverLayer__
#define __ctaoquan5__GameOverLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameOverLayerDelegate
{
public:
    virtual void gameOverLayerRestartGame()=0;
    
};

class GameOverLayer:public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    
    void setDelegate(GameOverLayerDelegate* delegate) {m_delegate=delegate;}
    
    void gameOver(int nowScore,int bestScore);
    
    
private:
    void clickRestartGame();
private:
    Label* m_labelTitle;
    Label* m_labelScoreMsg;
    
    GameOverLayerDelegate* m_delegate;
   
    
};

#endif /* defined(__ctaoquan5__GameOverLayer__) */
