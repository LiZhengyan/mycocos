//
//  ShoppingMall.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/16.
//
//

#include "ShoppingMall.h"
#include "DataUtil.h"
USING_NS_CC;
Scene* ShoppingMall::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ShoppingMall::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShoppingMall::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* shopBg=Sprite::create("shop/shopBG.jpg");
    shopBg->setScale(visibleSize.width/640);
    shopBg->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
    this->addChild(shopBg,1);
    
    _fileButton = MenuItemImage::create("shop/fileButton.png","shop/selectedFile.png",
                                           CC_CALLBACK_1(ShoppingMall::menuFileButtonCallback, this));
    _fileButton->setScale(visibleSize.width/640);
    _fileButton->setPosition(Vec2(origin.x + visibleSize.width*0.2 ,origin.y + visibleSize.height*0.8));
    
    _helpButton = MenuItemImage::create("shop/helpButton.png","shop/selectedHelp.png",
                                        CC_CALLBACK_1(ShoppingMall::menuHelpButtonCallback, this));
    _helpButton->setScale(visibleSize.width/640);
    _helpButton->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.8));

    
    _quanButton = MenuItemImage::create("shop/huanButton.png","shop/selectedQuan.png",
                                        CC_CALLBACK_1(ShoppingMall::menuQuanButtonCallback, this));
    _quanButton->setScale(visibleSize.width/640);
    _quanButton->setPosition(Vec2(origin.x + visibleSize.width*0.8 ,origin.y + visibleSize.height*0.8));
    
    
    _sx1Button = MenuItemImage::create("shop/s1.png","shop/s1ed.png",
                                        CC_CALLBACK_1(ShoppingMall::menuBuyFileButtonCallback, this));
    _sx1Button->setScale(visibleSize.width/640);
    _sx1Button->setTag(1);
    _sx1Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.55));
    
    _sx3Button = MenuItemImage::create("shop/s3.png","shop/s3ed.png",
                                       CC_CALLBACK_1(ShoppingMall::menuBuyFileButtonCallback, this));
    _sx3Button->setScale(visibleSize.width/640);
    _sx3Button->setTag(3);
    _sx3Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.45));
    
    
    _sx9Button = MenuItemImage::create("shop/s9.png","shop/s9ed.png",
                                       CC_CALLBACK_1(ShoppingMall::menuBuyFileButtonCallback, this));
    _sx9Button->setScale(visibleSize.width/640);
    _sx9Button->setTag(9);
    _sx9Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.35));
    
    
    
    
    _hx6Button = MenuItemImage::create("shop/H6.png","shop/H6ed.png",
                                       CC_CALLBACK_1(ShoppingMall::menuBuyHelpButtonCallback, this));
    _hx6Button->setScale(visibleSize.width/640);
    _hx6Button->setVisible(false);
    _hx6Button->setTag(6);
    _hx6Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.55));
    
    _hx15Button = MenuItemImage::create("shop/H15.png","shop/H15ed.png",
                                       CC_CALLBACK_1(ShoppingMall::menuBuyHelpButtonCallback, this));
    _hx15Button->setScale(visibleSize.width/640);
    _hx15Button->setVisible(false);
    _hx15Button->setTag(15);
    _hx15Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.45));
    
    
    _hx35Button = MenuItemImage::create("shop/H35.png","shop/H35ed.png",
                                       CC_CALLBACK_1(ShoppingMall::menuBuyHelpButtonCallback, this));
    _hx35Button->setScale(visibleSize.width/640);
    _hx35Button->setVisible(false);
    _hx35Button->setTag(35);
    _hx35Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.35));
    
    _qx5Button = MenuItemImage::create("shop/q5.png","shop/q5ed.png",
                                        CC_CALLBACK_1(ShoppingMall::menuBuyQuanButtonCallback, this));
    _qx5Button->setScale(visibleSize.width/640);
    _qx5Button->setVisible(false);
    _qx5Button->setTag(5);
    _qx5Button->setPosition(Vec2(origin.x + visibleSize.width*0.5 ,origin.y + visibleSize.height*0.55));
    
    
    
    MenuItemImage* closeMenu=MenuItemImage::create("shop/closeButton.png","shop/closeButton.png",
                                                   CC_CALLBACK_1(ShoppingMall::menuCloseButtonCallback, this));
    closeMenu->setScale(visibleSize.width/640);
    closeMenu->setPosition(Vec2(origin.x + visibleSize.width*0.9 ,origin.y + visibleSize.height*0.9));
    // create menu, it's an autorelease object
    auto menu = Menu::create(_fileButton,_helpButton,_quanButton,_sx1Button,_sx3Button,_sx9Button,_hx6Button,_hx35Button,_hx15Button,_qx5Button,closeMenu, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
    
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    _helpPropNumber=avm.asValueMap()["helpProp"].asInt();
    _filePropNumber=avm.asValueMap()["fileProp"].asInt();
    _circlePropNumber=avm.asValueMap()["circleProp"].asInt();
    
    char ownChar[10];
    sprintf(ownChar, "%d",_filePropNumber);
    _haveNumber=LabelAtlas::create(ownChar, "shop/shuzi.png", 22.3f, 94.0f, '0');
    _haveNumber->setAnchorPoint(Vec2(0, 0.5));
    _haveNumber->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.65));
    _haveNumber->setScale(visibleSize.width/640);
    this->addChild(_haveNumber,2);

    
    _effect=Sprite::create("shop/zuoyong.png");
    _effect->setScale(visibleSize.width/640);
    _effect->cocos2d::Node::setAnchorPoint(Vec2(0.5, 0.5));
    _effect->setPosition(Vec2(visibleSize.width*0.38, visibleSize.height*0.7));
    this->addChild(_effect,2);
    
    _have=Sprite::create("shop/yongyou.png");
    _have->setScale(visibleSize.width/640);
    _have->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.65));
    this->addChild(_have,2);

    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//    
//    this->addChild(label, 2);
    
    return true;
}

//归档按钮回调方法
void ShoppingMall::menuFileButtonCallback(Ref* pSender)
{
    _hx15Button->setVisible(false);
    _hx6Button->setVisible(false);
    _hx35Button->setVisible(false);
    _qx5Button->setVisible(false);
    _sx1Button->setVisible(true);
    _sx3Button->setVisible(true);
    _sx9Button->setVisible(true);
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage("shop/zuoyong.png");
    _effect->setPosition(Vec2(visibleSize.width*0.38, visibleSize.height*0.7));
    _effect->setTexture(texture);
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int fNumber=avm.asValueMap()["fileProp"].asInt();
    char ownChar[10];
    sprintf(ownChar, "%d",fNumber);
    _haveNumber->setString(ownChar);
}
//帮助按钮回调方法
void ShoppingMall::menuHelpButtonCallback(Ref* pSender)
{
    _qx5Button->setVisible(false);
    _sx1Button->setVisible(false);
    _sx3Button->setVisible(false);
    _sx9Button->setVisible(false);
    _hx15Button->setVisible(true);
    _hx6Button->setVisible(true);
    _hx35Button->setVisible(true);
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage("shop/helpZuoyong.png");
    _effect->setPosition(Vec2(visibleSize.width*0.52, visibleSize.height*0.7));
    _effect->setTexture(texture);
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int hNumber=avm.asValueMap()["helpProp"].asInt();
    char ownChar[10];
    sprintf(ownChar, "%d",hNumber);
    _haveNumber->setString(ownChar);
}
//圈按钮回调方法
void ShoppingMall::menuQuanButtonCallback(Ref* pSender)
{
     _qx5Button->setVisible(true);
    _hx15Button->setVisible(false);
    _hx6Button->setVisible(false);
    _hx35Button->setVisible(false);
    _sx1Button->setVisible(false);
    _sx3Button->setVisible(false);
    _sx9Button->setVisible(false);
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage("shop/quanZuoyong.png");
    _effect->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.7));
    _effect->setTexture(texture);
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int cNumber=avm.asValueMap()["circleProp"].asInt();
    char ownChar[10];
    sprintf(ownChar, "%d",cNumber);
    _haveNumber->setString(ownChar);
}
//购买归档道具按钮的回调方法
void ShoppingMall::menuBuyFileButtonCallback(cocos2d::Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int filePropNumber=avm.asValueMap()["fileProp"].asInt();
    char number[10];
    switch (button->getTag()) {
        case 1:
            DataUtil::updatePropData("fileProp", filePropNumber+1);
            sprintf(number, "%d",filePropNumber+1);
            _haveNumber->setString(number);
            break;
        case 3:
            DataUtil::updatePropData("fileProp", filePropNumber+3);
            sprintf(number, "%d",filePropNumber+3);
            _haveNumber->setString(number);
            break;
            
        case 9:
            DataUtil::updatePropData("fileProp", filePropNumber+9);
            sprintf(number, "%d",filePropNumber+9);
            _haveNumber->setString(number);
            break;
        default:
            break;
    }
}
//购买帮助道具按钮的回调方法
void ShoppingMall::menuBuyHelpButtonCallback(cocos2d::Ref* pSender)
{
    MenuItemImage* button=(MenuItemImage*)pSender;
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int helpPropNumber=avm.asValueMap()["helpProp"].asInt();
    
    
    char number[10];
    switch (button->getTag()) {
        case 6:
            DataUtil::updatePropData("helpProp", helpPropNumber+6);
            sprintf(number, "%d",helpPropNumber+6);
            _haveNumber->setString(number);
            break;
        case 15:
            DataUtil::updatePropData("helpProp", helpPropNumber+15);
            sprintf(number, "%d",helpPropNumber+15);
            _haveNumber->setString(number);
            break;
            
        case 35:
            DataUtil::updatePropData("helpProp", helpPropNumber+35);
            sprintf(number, "%d",helpPropNumber+35);
            _haveNumber->setString(number);
            break;
        default:
            break;
    }
    
}
//购买圈道具按钮的回调方法
void ShoppingMall::menuBuyQuanButtonCallback(cocos2d::Ref* pSender)
{
    char getUserSql[100];
    sprintf(getUserSql, "select * from Prop ");
    Value avm=DataUtil::getRow(getUserSql);
    int circlePropNumber=avm.asValueMap()["circleProp"].asInt();

    char number[10];
    DataUtil::updatePropData("circleProp", circlePropNumber+5);
    sprintf(number, "%d",circlePropNumber+5);
    _haveNumber->setString(number);
}
//关闭按钮的回调方法
void ShoppingMall::menuCloseButtonCallback(cocos2d::Ref* pSender)
{
    //发送通知，改变选择关卡界面的道具数
    EventCustom _event("shopUI");
    _eventDispatcher->dispatchEvent(&_event);
    Director::getInstance()->resume();
    Director::getInstance()->popScene();
}
