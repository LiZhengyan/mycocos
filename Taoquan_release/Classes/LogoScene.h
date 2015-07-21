//
//  LogoScene.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/15.
//
//

#ifndef __TaoQuan2__LogoScene__
#define __TaoQuan2__LogoScene__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;
class LogoScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
    void paeseXml();
    void loadXmlElement(XMLElement* rootElement);
    
};
#endif /* defined(__TaoQuan2__LogoScene__) */
