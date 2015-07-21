//
//  Tuowei.cpp
//  mytest5
//
//  Created by lizhengyan on 15/7/17.
//
//

#include "Tuowei.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* Tuowei::createScene()
{
    auto scene = Scene::create();
    auto layer = Tuowei::create();
    scene->addChild(layer);
    return scene;
}
bool Tuowei::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    size = Director::getInstance()->getVisibleSize();
    
    CCLayerColor* background = CCLayerColor::create(ccc4(255, 200, 255, 255), size.width, size.height);
    this->addChild(background);
    
    //存储子弹节点
    bulltArr = __Array::create();
    CC_SAFE_RETAIN(bulltArr);
    //存储 CCMotionStreak
    streakArr = __Array::create();
    CC_SAFE_RETAIN(streakArr);
    
    scheduleUpdate();
    
    return true;
}

void Tuowei::update(float delta)
{
    for (int i = 0; i < bulltArr->count(); i++) {
        CCSprite* bullt = (CCSprite*)bulltArr->objectAtIndex(i);
        bullt->setPositionY(bullt->getPositionY()+2);
        
        CCMotionStreak* streak = (CCMotionStreak*)streakArr->objectAtIndex(i);
        //每次调用setPosition函数重新设置对象位置时，“影子”将被创建并且慢慢渐隐  注：对于CCMotionStreak对象不可用getPosition()等方法。。
        streak->setPosition(bullt->getPosition());
    }
    
    for (int i = 0; i < bulltArr->count(); i++) {
        CCSprite* bullt = (CCSprite*)bulltArr->objectAtIndex(i);
        //删除超出屏幕节点
        if (bullt->getPositionY() >= size.height+bullt->getContentSize().height) {
            this->removeChild(bullt);
            bulltArr->removeObject(bullt);
            
            CCSprite* streak = (CCSprite*)streakArr->objectAtIndex(i);
            this->removeChild(streak);
            streakArr->removeObject(streak);
            
            break;
        }
    }
}

//拖尾效果类CCMotionStreak
//创建 子弹节点 和 CCMotionStreak对象
void Tuowei::createBullt(Point startPoint)
{
    Sprite* bullt = Sprite::create("bullet3.png");
    bullt->setPosition(startPoint);
    this->addChild(bullt,2);
    bulltArr->addObject(bullt);
    
    //第一个参数是间隐的时间，第二个参数是间隐片断的大小，第三个参数是贴图的宽高，第四个参数是颜色值RGB，第五个参数是贴图的路径或者贴图对象
    CCMotionStreak* streak = CCMotionStreak::create(0.8, 10, 10, ccRED, "1.png");
    streak->setPosition(startPoint);
    this->addChild(streak,1);
    streakArr->addObject(streak);
}

bool Tuowei::TouchBegan(Touch *pTouch, Event *pEvent)
{
    createBullt(pTouch->getLocation());
    return true;
}

void Tuowei::TouchMoved(Touch *pTouch, Event *pEvent){}
void Tuowei::TouchEnded(Touch *pTouch, Event *pEvent){}
void Tuowei::onEnter()
{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    CCLayer::onEnter();
}
void Tuowei::onExit()
{
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();
}

Tuowei::~Tuowei()
{
    CC_SAFE_RELEASE(bulltArr);
    CC_SAFE_RELEASE(streakArr);
}




