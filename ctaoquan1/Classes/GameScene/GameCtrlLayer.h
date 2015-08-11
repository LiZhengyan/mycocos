//
//  GameCtrlLayer.h
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#ifndef __FindRabbit__GameCtrlLayer__
#define __FindRabbit__GameCtrlLayer__

#include <stdio.h>

USING_NS_CC;

class GameCtrlLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameCtrlLayer);
    
private:
    void clickBackToMenu();
};

#endif /* defined(__FindRabbit__GameCtrlLayer__) */
