//
//  LogoScene.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/15.
//
//

#include "LogoScene.h"
#include "SelectLevel.h"
USING_NS_CC;

Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto spriteBG = Sprite::create("background.jpg");
    
    spriteBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    spriteBG->setScale(visibleSize.width/spriteBG->getContentSize().width,visibleSize.height/spriteBG->getContentSize().height);

    this->addChild(spriteBG, 0);
    auto logoSp = Sprite::create("logo.png");
    logoSp->setScale(visibleSize.width*0.9/640);
    logoSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*0.6 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(logoSp, 2);
    
    this->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        //跳转到选择关卡界面
        Scene* selectLevelScene=SelectLevel::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.2f, selectLevelScene));
    }),NULL));
    
     paeseXml();

    return true;
}

void LogoScene::paeseXml()
{
    ValueVector xmlVector;
    
    //    //xml解析
    //string fileName="loadXml";
    //std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;
    
    //std::string filePath=cocos2d::FileUtils::getInstance()->getStringFromFile("loadPicture.xml");
    //获取文件在系统的绝对路径
    //std::string filePath1=FileUtils::getInstance()->fullPathForFilename("loadPicture.xml");
    //log("%s",filePath1.c_str());
    XMLDocument *pDoc = new XMLDocument();
    Data fileData=FileUtils::getInstance()->getDataFromFile("loadPicture.xml");
    pDoc->Parse((const char*)fileData.getBytes());//开始解析
//    XMLError errorId = pDoc->LoadFile(filePath1.c_str());
//    if (errorId != 0) {
//        //xml格式错误
//        log("cuowu");
//    }
    //获取第一个节点属性
    XMLElement *rootEle = pDoc->RootElement();
    const XMLAttribute *attribute = rootEle->FirstAttribute();
    //打印节点属性名和值
    log("attribute<em>name = %s,attribute</em>value = %s", attribute->Name(), attribute->Value());
    
    loadXmlElement(rootEle);
    delete pDoc;
}

void LogoScene::loadXmlElement(XMLElement* rootElement)
{
    XMLElement *dicEle = rootElement->FirstChildElement();
    while (dicEle!=NULL) {
        if (dicEle->GetText()!=NULL) {
            log("dicEle Text= %s", dicEle->GetText());
            string name=dicEle->GetText();
            string png=".png";
            //判断是否是图片
            if (name.find(png)<100) {
                log("%lu 是图片",name.find(png));
                //加入缓存
                Director::getInstance()->getTextureCache()->addImageAsync(dicEle->GetText(),CC_CALLBACK_1(LogoScene::menuCloseCallback, this));
                Texture2D* texture=TextureCache::sharedTextureCache()->textureForKey(dicEle->GetText());
                if (texture) {
                    texture->setAntiAliasTexParameters();
            }
            
            
            }
            
            
        }else if (dicEle->FirstChildElement()!=NULL)
        {
            loadXmlElement(dicEle);
        }
        dicEle=dicEle->NextSiblingElement();
    }
}

void LogoScene::menuCloseCallback(Ref* pSender)
{
    log("成功!!!!");
}