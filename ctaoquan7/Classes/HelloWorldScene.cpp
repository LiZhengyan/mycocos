#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;
#define MAX_COUNT 20

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize= Director::getInstance()->getVisibleSize();
    Vec2 origin=Director::getInstance()->getVisibleOrigin();
    
    
    auto label1=LabelTTF::create("START","Arial",64);
    MenuItem* menuitem =MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::clickstartGame, this));
    Menu* menuStart = Menu::create(menuitem,NULL);
    menuitem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    menuStart->setPosition(Vec2::ZERO);
    this->addChild(menuStart,1,101);
    
    auto label2=LabelTTF::create("START2","Arial",64);
    MenuItem* menuitem2 =MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::menucloseCallBack, this));
    Menu* menuStart2 = Menu::create(menuitem2,NULL);
    menuitem2->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2-100));
    menuStart2->setPosition(Vec2::ZERO);
    this->addChild(menuStart2,1,102);
    
    
    auto label3=LabelTTF::create("START3","Arial",64);
    MenuItem* menuitem3 =MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::clickstartGame3, this));
    Menu* menuStart3 = Menu::create(menuitem3,NULL);
    menuitem3->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2+100));
    menuStart3->setPosition(Vec2::ZERO);
    this->addChild(menuStart3,1,103);
    
    
    
    
    
    this->list=Vector<Sprite*>(MAX_COUNT);   //列表容器 Vector<T>
    for (int i =0 ; i<MAX_COUNT; i++) {
        Sprite* sprite = Sprite::create("res/guangbo.png");
        list.pushBack(sprite);
    }
    
    dict1=__Dictionary::create();
    dict2=__Dictionary::create();
    dict1->retain();
    dict2->retain();
    
    map1= Map<std::string, Sprite *>();
    map2= Map<std::string, Sprite *>();
    
    
    for (int i=0; i<MAX_COUNT; ++i) {
        auto sprite1=Sprite::create("res/starLight3.png");
        this->dict1->setObject(sprite1, i);
        
        auto sprite2=Sprite::create("res/starLight2.png");
        __String * key=__String::createWithFormat("key %d",i);
        this->dict2->setObject(sprite2, key->getCString()); //__dictinary字典
        
        
        
        __String * keyname=__String::createWithFormat("KEY(%d)",i);
        map1.insert(keyname->getCString(), sprite1);                    //map<k,y>容器
        map2.insert(keyname->getCString(), sprite2);
        
        
        Value spname("startLight.png");
        vlist.push_back(spname); //ValueVector容器
        
        
        __String * keyname3=__String::createWithFormat("VMAP(%d)",i); //ValueMap字典容器
//        mlist.at(keyname3->getCString())=sprite1; //这样是错误的。
        char name[100];
        std::sprintf(name ,"key_%d",i);
        std::pair<std::string,Value> pair1(name,Value("res/start.png"));
        mlist.insert(pair1);
        
    }
    
    return true;
}




void HelloWorld::clickstartGame3(cocos2d::Ref *Psender)
{
    auto item=(MenuItem*)Psender;
    Size visibleSize= Director::getInstance()->getVisibleSize();
    int x = CCRANDOM_0_1()*visibleSize.width;
    int y = CCRANDOM_0_1()*visibleSize.height;
    log("x=%d,y=%d",x,y);
    item->setPosition(Vec2(x,y));
    log("List=count=%zd",this->list.size());
    
//    for(auto&v:vlist){
//        __String * name=__String::createWithFormat("%s/%s","res",v.asString().c_str());
//        log("string=%s",name->getCString());
//        
//        
//    }
    for(auto&v:mlist){
        log("%s-%s",v.first.c_str(),v.second.asString().c_str());
    }
    
}


void HelloWorld::clickstartGame(cocos2d::Ref *Psender)
{
    log("List=count=%zd",this->list.size());
    Size visibleSize= Director::getInstance()->getVisibleSize();
   
    for (const auto&sprite: list) {
        int x = CCRANDOM_0_1()*visibleSize.width;
        int y = CCRANDOM_0_1()*visibleSize.height;
        
        sprite->setPosition(Vec2(x, y));
        this->removeChild(sprite);
        this->addChild(sprite);
    }
    
    
    
}


void HelloWorld::menucloseCallBack(Ref* pSender)
{
    Size visibleSize= Director::getInstance()->getVisibleSize();
    DictElement* pElement;
    CCDICT_FOREACH(dict1, pElement)
    {
        long key = pElement->getIntKey();
        log("Add Sprite %zd",key);
        auto sprite = (Sprite*) pElement->getObject();
        int x =CCRANDOM_0_1()*visibleSize.width;
        int y =CCRANDOM_0_1()*visibleSize.height;
        sprite->setPosition(Vec2(x, y));
        this->removeChild(sprite);
        this->addChild(sprite);
    }
    
    CCDICT_FOREACH(dict2, pElement)
    {
        const char * key=pElement->getStrKey();
        log("Add Sprite %zd",key);
        auto sprite = (Sprite*) pElement->getObject();
        int x =CCRANDOM_0_1()*visibleSize.width;
        int y =CCRANDOM_0_1()*visibleSize.height;
        sprite->setPosition(Vec2(x, y));
        this->removeChild(sprite);
        this->addChild(sprite);
    }
    
    std::vector<std::string> mapkeyVec1;
    mapkeyVec1 = this->map1.keys();
    for(auto key:mapkeyVec1){
        Sprite* sprite =(Sprite*)this->map1.at(key);
        log("%s=%p",key.c_str(),sprite);
    }
    
    
    

}


HelloWorld::~HelloWorld()
{
    this->dict1->removeAllObjects();
    CC_SAFE_RELEASE_NULL(this->dict1);
    this->dict2->removeAllObjects();
    CC_SAFE_RELEASE_NULL(this->dict2);
    
    
}