//
//  MenuCtrlLayer.h
//  FindRabbit
//
//  Created by yangjh on 15/4/23.
//
//

#ifndef __FindRabbit__MenuCtrlLayer__
#define __FindRabbit__MenuCtrlLayer__

#include <stdio.h>

USING_NS_CC;

class MenuCtrlLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MenuCtrlLayer);
    
private:
    void clickStartGame();
};

#endif /* defined(__FindRabbit__MenuCtrlLayer__) */
