//
//  LoadScene.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/8/5.
//
//

#ifndef __TaoQuan2__LoadScene__
#define __TaoQuan2__LoadScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
class LoadScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    
    virtual void onTouchMoved(Touch *touch, Event *event);
    
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    virtual void onTouchCancelled(Touch *touch, Event *event);

    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadScene);
    void paeseXml();
    void loadXmlElement(XMLElement* rootElement);
    
    int _totalNum;
    int _haveLoadNum;
    
    Size visibleSize;
    Vec2 origin;
    
};
#endif /* defined(__TaoQuan2__LoadScene__) */
