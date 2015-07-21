//
//  ShoppingMall.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/16.
//
//

#ifndef __TaoQuan2__ShoppingMall__
#define __TaoQuan2__ShoppingMall__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class ShoppingMall : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void menuFileButtonCallback(cocos2d::Ref* pSender);
    void menuHelpButtonCallback(cocos2d::Ref* pSender);
    void menuQuanButtonCallback(cocos2d::Ref* pSender);
    
    void menuBuyFileButtonCallback(cocos2d::Ref* pSender);
    void menuBuyHelpButtonCallback(cocos2d::Ref* pSender);
    void menuBuyQuanButtonCallback(cocos2d::Ref* pSender);
    void menuCloseButtonCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(ShoppingMall);
    
    MenuItemImage* _fileButton;
    MenuItemImage* _helpButton;
    MenuItemImage* _quanButton;
    
    MenuItemImage* _sx1Button;
    MenuItemImage* _sx3Button;
    MenuItemImage* _sx9Button;
    
    MenuItemImage* _hx6Button;
    MenuItemImage* _hx15Button;
    MenuItemImage* _hx35Button;
    
    MenuItemImage* _qx5Button;

    Sprite* _effect;
    Sprite* _have;
    Sprite* _effectLabel;
    LabelAtlas* _haveNumber;
    
    
    int _helpPropNumber;
    int _filePropNumber;
    int _circlePropNumber;
    
    Size visibleSize;
    Vec2 origin;
    
};
#endif /* defined(__TaoQuan2__ShoppingMall__) */
