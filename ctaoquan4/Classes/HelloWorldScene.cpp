#include "HelloWorldScene.h"
#include "GameScene.h"

//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;
//using namespace cocostudio;
//using namespace cocostudio::timeline;
//using namespace cocos2d::ui;

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
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    Node* node1 = dynamic_cast<Node*>(rootNode->getChildByName("ProjectNode_1"));
    
    
    Button* button = dynamic_cast<Button*>(node1->getChildByName("Button_1"));
    
//    auto layNode = CSLoader::createNode("selectlevel/Layer.csb");
    addChild(rootNode);
//    addChild(layNode);
    //通过按钮的名字获得按钮
//    Button* button = dynamic_cast<Button*>(->getChildByName("Button_1"));
//    
//    Button* button1 = dynamic_cast<Button*>(rootNode->getChildByName("Button_4"));
//    button1->setPosition(Vec2(100,200));
//   button->setPosition(Vec2(100,200));
//    button->setPosition(Vec2(200,200));
    
    
//    button->addTouchEventListener(HelloWorld::menuCloseCallback)
    
//添加监听
    button->addTouchEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    auto gameScene=GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);

}

void HelloWorld::Option(Ref* pSender, Widget::TouchEventType type)
{
    switch(type)
    {
            //按下按钮
        case Widget::TouchEventType::BEGAN:
        {
            log("Down !");
        }
            break;
            
            //松开按钮
        case Widget::TouchEventType::ENDED:
        {
            log("Up !");
        }
            break;
            
            //在按钮上移动
        case Widget::TouchEventType::MOVED:
        {
            log("Move !");
        }
            break;
            
            //取消按钮
        case Widget::TouchEventType::CANCELED:
        {
            log("Cancel !");
        }
            break;
        default:
            break;
    }
}