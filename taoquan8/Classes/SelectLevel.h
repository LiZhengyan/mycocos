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

USING_NS_CC_EXT;
USING_NS_CC;
class SelectLevel:public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(SelectLevel);

    void menuCloseCallback(Ref* pSender);
    
    //以下是注册触摸事件和实现各种的touch函数
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);
    //最后这个函数来校验每个关卡的位置，是各个关卡都位于屏幕的中央
    void adjustScrollView(float offset);
    
    void menuMusicCallback(cocos2d::Ref* pSender);
    void menuChengjiuCallback(cocos2d::Ref* pSender);
    void menuShareCallback(cocos2d::Ref* pSender);
    void menuCundangCallback(cocos2d::Ref* pSender);
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
