//
//  achievement.cpp
//  Taoquan_release
//
//  Created by lizhengyan on 15/8/9.
//
//

#include "achievement.h"
#include "DataUtil.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;


// on "init" you need to initialize your instance
bool Achievement::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin  = Director::getInstance()->getVisibleOrigin();
    //返回selectLevel界面按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Achievement::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    //achievement/bg.png
    
    chengjiuBG=Sprite::create("chengjiu/bg.png");
    chengjiuBG->setScale(visibleSize.width/chengjiuBG->getContentSize().width,visibleSize.height/chengjiuBG->getContentSize().height);
    chengjiuBG->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
    chengjiuBG->setOpacity(0);
    chengjiuBG->runAction(FadeTo::create(0.3, 255));
    this->addChild(chengjiuBG,0);
    //迷城
    auto michengItem = MenuItemImage::create(
                                           "achievement/micheng.png",
                                           "achievement/selectedMicheng.png",
                                           CC_CALLBACK_1(Achievement::michengCallback, this));
    
    michengItem->setPosition(Vec2(origin.x + visibleSize.width*0.15 ,
                                origin.y + visibleSize.height*0.825));
    michengItem->setScale(visibleSize.width/chengjiuBG->getContentSize().width);
    
    //星空
    
    auto xinkongItem = MenuItemImage::create(
                                             "achievement/xinkong.png",
                                             "achievement/selectedXinkong.png",
                                             CC_CALLBACK_1(Achievement::xinkongCallback, this));
    
    xinkongItem->setPosition(Vec2(origin.x + visibleSize.width*0.3 ,
                                  origin.y + visibleSize.height*0.825));
    xinkongItem->setScale(visibleSize.width/chengjiuBG->getContentSize().width);
    
    
    
    auto menu = Menu::create(closeItem,michengItem, xinkongItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    //创建一个talbleview  tableview的显示区域大小为 宽的0.8 高的0.6
    TableView* tableView = TableView::create(this, Size(Vec2(visibleSize.width*0.8,visibleSize.height*0.6)));
    //设置tableview为水平方向  ScrollView::Direction::VERTICAL 为垂直,ScrollView::Direction::HORIZONTAL 为水平
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    //设置位置
    tableView->ignoreAnchorPointForPosition(false);
    tableView->setAnchorPoint(Vec2(0.5,0.5));//设置锚点
    tableView->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.4));
    //设置代理对象
    tableView->setDelegate(this);
    // 填充顺序
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    //添加tableview到当前layer
    this->addChild(tableView);
    //加载tableview  
    tableView->reloadData();
    
    return true;
    
}


//当cell被点击时调用  cell->getIdx()获取当前点击cell的编号
void Achievement::tableCellTouched(TableView* table, TableViewCell* cell)
{
    // 在输出窗口打印出，当前cell的编号
    CCLOG("cell touched at index: %zi", cell->getIdx());
}

//设置编号为 idx 的cell的大小
Size Achievement::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(visibleSize.width*0.9, visibleSize.height*0.1);
}

//由于tableview是动态获取数据的，该方法在初始化时会被调用一次，之后在每个隐藏的cell显示出来的时候都会调用
TableViewCell* Achievement::tableCellAtIndex(TableView *table, ssize_t idx)
{
    
    // 在重用队列中获取一个cell 然后判断cell是否为空 不为空则创建一个新的
    TableViewCell *cell = table->dequeueCell();
    log("%zd",idx);
//    if (!cell) {
        log("cell is null");
        //创建一个新的cell
        cell = new TableViewCell();
        //加入到自动释放池中
        cell->autorelease();
        //创建一个图片精灵
        Sprite *sprite = CCSprite::create("chengjiu/s1.png");
        Sprite *sprite1= Sprite::create("chengjiu/false.png");
//        Sprite *dz= Sprite::create("chengjiu/dz.png");
        //设置精灵锚点
        sprite->setAnchorPoint(Vec2(0,0.5));   //右中
        sprite1->setAnchorPoint(Vec2(1,0.5));  //左中
//        dz->setAnchorPoint(Vec2(0.5,0.5));
        sprite->setScale(visibleSize.width/chengjiuBG->getContentSize().width);sprite1->setScale(visibleSize.width/chengjiuBG->getContentSize().width);//dz->setScale(visibleSize.width/chengjiuBG->getContentSize().width,visibleSize.height/chengjiuBG->getContentSize().height);
        //设置精灵位置 相当于在cell中的相对位置
        sprite->setPosition(Vec2(visibleSize.width*0.01,visibleSize.height*0.05) );
        sprite1->setPosition(Vec2(visibleSize.width*0.8,visibleSize.height*0.05) );
//        dz->setPosition(Vec2(visibleSize.width*0.4,visibleSize.height*0.04));
        //将精灵加入到cell中
//        cell->setAnchorPoint(Vec2(0.5,0.5));
        cell->addChild(sprite);cell->addChild(sprite1);//cell->addChild(dz);
//    }

    return cell;
}

//设置cell的个数 即一个tableview中包含了20个cell
ssize_t Achievement::numberOfCellsInTableView(TableView *table)
{
    return 20;
}

void Achievement::menuCloseCallback(Ref* pSender)
{
    this->removeFromParent();
    
}


void Achievement::michengCallback(Ref* pSender)
{
    this->removeFromParent();
    
}


void Achievement::xinkongCallback(Ref* pSender)
{
    this->removeFromParent();
    
}