#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto Winsize =Director::getInstance()->getWinSize();
    
    
    
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
//    rootNode->setContentSize(visibleSize);
//    ui::Helper::doLayout(rootNode);
    addChild(rootNode);
    
    


    
    
    
    
    int height_dx = int(visibleSize.height);
    int width_dx = int(visibleSize.width);
    int xy[][2]={{3,85},{3,55},{27,85},{27,55},{15,80},{16,60},{8,70},{23,69},{16,69}};
    
    for (int i=0; i<9 ; i++)
    {
            log("%d,%d",xy[i][0],xy[i][1]);
            auto mysp = Sprite::create("1.png");
            this->addChild(mysp);
            mysp->setPosition(Vec2((height_dx/50)*xy[i][0],(width_dx/50)*xy[i][1]));
            log("==>%d,%d",(height_dx/50)*xy[i][0],(width_dx/50)*xy[i][1]);
            mysp->setScale(0.4);
    }
    
    log("%f,%f",height_dx,width_dx);
    
    
//    for( int h =1 ;h<=height_dx;h++)
//    {
//        
//        char name[20];
//        sprintf(name,"selectlevel/%d.png",int(h%9)+1);
//        
//        log("%s",name);
//        
//        for (int w=1 ; w<=width_dx;w++)
//        {
//            log("%d,%d,%d,%d",h,w,h*10,w*10);
//            auto mysp = Sprite::create(name);
//            this->addChild(mysp);
//            mysp->setPosition(Vec2(w*10,h*10));
//            mysp->setScale(0.1);
//            
//        }
//    }
    
    log("%f,%f",visibleSize.width,visibleSize.height);
    log("%f,%f",origin.x,origin.y);
    return true;
}
