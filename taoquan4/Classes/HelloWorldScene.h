#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ResolvePicture.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    void updateTime(float dt);
    void update(float dt);
    
    Sprite* spriteTiao;
    ProgressTimer* powerProgress;
    Sprite* spriteQuan;
    
    Vector<ResolvePicture*> spriteVector;
    Vector<ResolvePicture*> bigPictureVector;
    int quanNumber;
    char quanNumberLabel[10];
    float x;float y;
    Sprite* bigPicture;
    
    ResolvePicture* gengDown;
    ResolvePicture* duoDown;
    ResolvePicture* youDown;
    ResolvePicture* xiDown;
private:
    LabelTTF* label;
    LabelTTF* numberLabel;
    Size visibleSize ;
    Vec2 origin;
};

#endif // __HELLOWORLD_SCENE_H__
