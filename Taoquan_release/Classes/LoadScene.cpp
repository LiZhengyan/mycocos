//
//  LoadScene.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/8/5.
//
//

#include "LoadScene.h"
#include "SelectLevel.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* LoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _totalNum=318;
    _haveLoadNum=0;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto spriteBG = Sprite::create("jiazai/jiazaiBG.png");
    
    spriteBG->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    spriteBG->setScale(visibleSize.width/spriteBG->getContentSize().width,visibleSize.height/spriteBG->getContentSize().height);
    
    this->addChild(spriteBG, 0);
    
    auto loadSprite = Sprite::create("jiazai/loading.png");
    loadSprite->setScale(visibleSize.width*0.6/640);
    loadSprite->setPosition(Vec2(visibleSize.width*0.4 + origin.x, visibleSize.height*0.05 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(loadSprite, 2);
    
    
    paeseXml();
    
    //音乐音效的加载
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musicAndeffect/selectLevelMusic.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("musicAndeffect/selectLevelButtonEffect.wav");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musicAndeffect/gameSceneMusic.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("musicAndeffect/buttonEffect.wav");
    UserDefault::getInstance()->setBoolForKey("isSound", true);


    
    //添加监听
    auto _eventDispatcher=Director::getInstance()->getEventDispatcher();
    auto listener1=EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchMoved=CC_CALLBACK_2(LoadScene::onTouchMoved, this);
    listener1->onTouchBegan=CC_CALLBACK_2(LoadScene::onTouchBegan,this);
    listener1->onTouchEnded=CC_CALLBACK_2(LoadScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    return true;
}

void LoadScene::paeseXml()
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

void LoadScene::loadXmlElement(XMLElement* rootElement)
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
                Director::getInstance()->getTextureCache()->addImageAsync(dicEle->GetText(),CC_CALLBACK_1(LoadScene::menuCloseCallback, this));
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
static int i=0;
void LoadScene::menuCloseCallback(Ref* pSender)
{
    //log("成功!!!!");
    _haveLoadNum++;
    if (_haveLoadNum%60==0) {
        i++;
        
        auto loadSprite = Sprite::create("jiazai/jiazaiDian.png");
        loadSprite->setScale(visibleSize.width*0.3/640);
        loadSprite->setPosition(Vec2(visibleSize.width*(0.45+i*0.05) + origin.x, visibleSize.height*0.05 + origin.y));
        this->addChild(loadSprite, 2);
        
    }
    //log("++++++++%d====%d",i,_haveLoadNum);
    if (_haveLoadNum==_totalNum) {
        i=6;
        auto loadSprite = Sprite::create("jiazai/jiazaiDian.png");
        loadSprite->setScale(visibleSize.width*0.3/640);
        loadSprite->setPosition(Vec2(visibleSize.width*(0.45+i*0.05) + origin.x, visibleSize.height*0.05 + origin.y));
        this->addChild(loadSprite, 2);
        //跳转到选择关卡界面
        Scene* selectLevelScene=SelectLevel::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.2f, selectLevelScene));
    }

    
}
bool LoadScene::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void LoadScene::onTouchMoved(Touch *touch, Event *event)
{}

void LoadScene::onTouchEnded(Touch *touch, Event *event)
{
}

void LoadScene::onTouchCancelled(Touch *touch, Event *event)
{}


