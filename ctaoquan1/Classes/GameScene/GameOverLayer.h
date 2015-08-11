//
//  GameOverLayer.h
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#ifndef __FindRabbit__GameOverLayer__
#define __FindRabbit__GameOverLayer__

#include <stdio.h>

USING_NS_CC;

class GameOverLayerDelegate
{
public:
    virtual void gameOverLayerRestartGame() = 0;
};

class GameOverLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    
    // 设置代理
    void setDelegate(GameOverLayerDelegate *delegate) { m_delegate = delegate; }
    // 游戏结束
    void gameOver(int nowScore, int bestScore);
    
private:
    // 点击重新开始按钮
    void clickRestartGame();
    
private:
    Label *m_labelTitle;
    Label *m_labelScoreMsg;
    // 回调
    GameOverLayerDelegate *m_delegate;
};

#endif /* defined(__FindRabbit__GameOverLayer__) */
