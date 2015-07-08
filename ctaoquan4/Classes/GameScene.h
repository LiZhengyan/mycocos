//
//  GameScene.h
//  ctaoquan4
//
//  Created by lizhengyan on 15/6/18.
//
//

#ifndef __ctaoquan4__GameScene__
#define __ctaoquan4__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class GameScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menufanghui(cocos2d::Ref* pSender);
    void Option(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);

    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    bool collisionWithCircle(cocos2d::Vec2 circlePoint,float radius,cocos2d::Vec2 circlePointTwo, float radiusTwo);
    
    // implement the "static create()" method manually
    
    
    void updateTime(float dt);
    void update(float dt);
    
    
    ProgressTimer* powerProgress;
    Sprite* g_zhizheng_1;
    Sprite* spriteQuan;
    Vector<Node*> game1_sp1_list;
    Node*   game1_lay;
    
    
    float x;float y;
    bool isTouch;
    
    int quanNumber=100;
    char quanNumberLabel[10];
    
private:
    LabelTTF* label;
    Text * numberLabel;
    Size visibleSize ;
    Vec2 origin;
};




#endif /* defined(__ctaoquan4__GameScene__) */
