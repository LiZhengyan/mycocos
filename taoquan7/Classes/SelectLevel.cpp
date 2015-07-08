//
//  SelectLevel.cpp
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#include "SelectLevel.h"
#include "GameScene.h"
USING_NS_CC;
Scene* SelectLevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SelectLevel::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //数据库测试
     DataUtil::initDB("ok.db");
    
    string sqlssss = "drop table picture";
    DataUtil::deleteData(sqlssss);
    
    //数据库中美有表格的话就先创建一个表格先
    string sqlsss = "create table picture(id integer,level integer,name text,isCover bool)";
     DataUtil::createTable(sqlsss,"picture");
    
    //像表格中插入数据
     string sqlss = "insert into picture values(1,1,'1.png','false')";
     DataUtil::insertData(sqlss);
    
    /*string sqls = "delete from user where id=1";
     DataUtil::deleteData(sqls);*/
    /*string sqls = "update user set username='小猪猪猪猪' where id=1";
     DataUtil::updateData(sqls);*/
    
    
    /*string sqlsssss = "select count(*) from user";
     int a = DataUtil::getDataCount(sqlsssss);*/
    string sqlssssss = "select * from picture where id=1";
    Sprite *pp = Sprite::create();
    DataUtil::getDataInfo(sqlssssss,pp);
    //最后别忘了关闭数据库哦
        DataUtil::closeDB();

    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    this->addChild(label, 1);
    
    auto sprite = Sprite::create("selectlevel/BG.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    sprite->setScale(visibleSize.width/sprite->getContentSize().width);
    this->addChild(sprite, 0);
    
    for (int i=0; i<3; i++) {
        for (int j=1; j<4; j++) {
            char name[20];
            sprintf(name, "selectlevel/%d.png",i*3+j);
            auto levelButton = MenuItemImage::create(name,name,CC_CALLBACK_1(SelectLevel::menuCloseCallback, this));
            levelButton->setScale(visibleSize.width/640);
            levelButton->setPosition(Vec2(visibleSize.width/4*j,visibleSize.height*0.727-(visibleSize.height*0.09+visibleSize.height*0.038)*i));
            
            auto menu = Menu::create(levelButton, NULL);
            menu->setPosition(Vec2::ZERO);
            this->addChild(menu, 2);
        }

    }
        
    return true;
}
                    
void SelectLevel::menuCloseCallback(Ref* pSender)
{
//    Director::getInstance()->end();
//            
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//            exit(0);
//#endif
    Scene* gameScene=GameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);

}

