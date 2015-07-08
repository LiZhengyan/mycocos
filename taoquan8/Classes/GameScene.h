//
//  GameScene.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#ifndef __TaoQuan__GameScene__
#define __TaoQuan__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "ResolvePicture.h"
USING_NS_CC;

class GameScene :public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    void updateTime(float dt);
    void update(float dt);
    
    void setPicturePosition(int num);
    
    
    Sprite* spriteTiao;
    ProgressTimer* powerProgress;
    Sprite* spriteQuan;
    
    Vector<ResolvePicture*> spriteVector;
    Vector<ResolvePicture*> bigPictureVector;
    int quanNumber;
    char quanNumberLabel[10];
    float x;float y;
    Sprite* bigPicture;
    
    bool isTouch;
    
    ValueVector positionNumber;
    
private:
    LabelAtlas* labelTime;
    LabelAtlas* labelNumber;
    Size visibleSize ;
    Vec2 origin;
};
#endif /* defined(__TaoQuan__GameScene__) */
