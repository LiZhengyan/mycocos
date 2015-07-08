#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Snow.h"

USING_NS_CC;

using namespace cocostudio::timeline;

//Scene* HelloWorld::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer1 = Snow::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer1);
//
//    // return the scene
//    return scene;
//}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    auto rootNode = CSLoader::createNode("selectlevel.csb");
//    auto rootNode = CSLoader::createNode("gamescene.csb");
//
//    addChild(rootNode);
    auto label1=LabelTTF::create("Hello World", "Arial", 64);
    MenuItemLabel * menuLael1 = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::clickstartGame,this));
    Menu* menuStart = Menu::create(menuLael1,NULL);
    menuStart->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-label1->getContentSize().height)/2);
    
    
    auto label2=LabelAtlas::create("1100", "res/gamescene/shuzi2.png", 26.0f, 41.0f,'0');
    label2->setPosition(Vec2(origin.x+visibleSize.width/2,menuStart->getPositionY()-200));
    
    
    auto label3=Label::createWithSystemFont("Hello World!!!", "Arial", 60);
    label3->setPosition(Vec2(origin.x+visibleSize.width/2,label2->getPositionY()-300));
    
//    label3->enableShadow(Color4B(255,255,255,128),Size(4,-4));
    
    this->addChild(label2);
    this->addChild(label3);
    this->addChild(menuStart);
    

    return true;
}


void HelloWorld::clickstartGame(Ref* Sender)
{
    this->removeChildByTag(100);
    this->addChild(Snow::create(),0,100);
    
    
}
