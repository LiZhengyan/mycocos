#ifndef __PARTICLEDEMO_SCENE_H__
#define __PARTICLEDEMO_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class Particledemo : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(Particledemo);
};

#endif 