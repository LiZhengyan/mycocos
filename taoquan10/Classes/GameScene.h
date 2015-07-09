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
#include "ShadeLayer.h"
#include "FailedShadeLayer.h"
#include "PauseLayer.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuBackCallback(cocos2d::Ref* pSender);//返回按钮回调方法
    void menuPauseCallback(Ref* pSender);//暂停按钮回调方法
    void menuResartCallback(cocos2d::Ref* pSender);//重新开始按钮回调方法
    void menuHelpCallback(Ref* pSender);//帮助按钮回调方法
    
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    
    void updateTime(float dt);
    void update(float dt);
    
    void setNextLevelPicture(EventCustom* e);//自定义监听，下一关的回调方法
    void resetGame(EventCustom* e);//自定义监听，重新开始的回调方法
    
    
    void enterIntoSucceedUI();
    void enterIntoFailedUI();
    
    //按两次退出
    void menuCloseCallback(Ref* pSender);
    void CloseExitSign(float dt);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    bool _IsNeedExit;
    
    Sprite* _spriteTiao;
    ProgressTimer* _powerProgress;
    Sprite* _spriteQuan;
    //QuanSprite* spriteQuan;

    
    Vector<ResolvePicture*> spriteVector;//小图
    Vector<ResolvePicture*> hiddenPictureVector;//隐藏的小图
    Vector<ResolvePicture*> showPictureVector;//隐藏的小图
    Vector<Sprite*> dizuoVector;//底座
    Vector<Sprite*> dizuoTouyingVector;//底座投影
    Vector<Sprite*>waterVector;
    
    int _timeNumber;//时间
    int _loopNumber;//环数
    char _loopNumberLabel[10];
    float x;float y;
    
    bool _isTouch;//判断是否可触摸
    bool _isLoopOrigin;//判断环是否在原来位置
    bool _isBeganGame;
    
    ShadeLayer* _succeedLayer;//过关的层
    FailedShadeLayer* _failLayer;//失败层
    PauseLayer* _pauseLayer;
    
    Sprite* _wholePicture;//全图
    Sprite* _gameBG;
    
    ~GameScene();

    
private:
    LabelAtlas* labelTime;
    LabelAtlas* labelNumber;
    Size visibleSize ;
    Vec2 origin;
    
    MenuItemImage*pauseItem;
    MenuItemImage*resumeItem;
};
#endif /* defined(__TaoQuan__GameScene__) */