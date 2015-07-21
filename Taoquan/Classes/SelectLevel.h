//
//  SelectLevel.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#ifndef __TaoQuan__SelectLevel__
#define __TaoQuan__SelectLevel__

#include <stdio.h>
#include "cocos2d.h"
#include "DataUtil.h"
#include "cocos-ext.h"
#include "AlertLayer.h"
USING_NS_CC_EXT;
USING_NS_CC;
class SelectLevel:public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectLevel);
    
    Size visibleSize;
    Vec2 origin;
    
    ~SelectLevel();

    void menuLevelButtonCallback(Ref* pSender,int level,bool issuo,bool isfile);//关卡按钮的回调方法
    void leftAndRightAdjustScrollView(Ref* pSender);//左右按钮的回调方法
    
    void alertIsFileFunction();//提示是否存档
    void menuIsFileBttonCallback(EventCustom* e);//是否存档按钮的回调函数
    void callBackPropNumberChange(EventCustom* e);
    
    //以下是注册触摸事件和实现各种的touch函数
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    //最后这个函数来校验每个关卡的位置，是各个关卡都位于屏幕的中央
    void adjustScrollView(float offset);
    
    //按两次退出
    void menuCloseCallback(Ref* pSender);
    void CloseExitSign(float dt);
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    
    void menuMusicCallback(cocos2d::Ref* pSender);
    void menuChengjiuCallback(cocos2d::Ref* pSender);
    void menuShareCallback(cocos2d::Ref* pSender);
    void menuCundangCallback(cocos2d::Ref* pSender);
    
    //是否解锁
    bool m_IsNeedExit;
    bool _isSound;
    
    
    LabelAtlas* _sPropNumber;
    LabelAtlas* _hPropNumber;
    LabelAtlas* _cPropNumber;
    
    MenuItemImage* _leftButton;
    MenuItemImage* _rightButton;
    
    AlertLayer* _alertLayer;//弹窗层
    
    Vector<MenuItemImage*>menuVector;
     Vector<LabelAtlas*>propNumberVector;
    
    
private:
    //将CCScrollView作为自己的层添加进来
    ScrollView * m_scrollView;
    //触摸点的位置
    Point m_touchPoint;
    //CCScrollView的便宜量
    Point m_offsetPoint;
    //当前为第几个关卡
    int m_nCurPage;
};

#endif /* defined(__TaoQuan__SelectLevel__) */
