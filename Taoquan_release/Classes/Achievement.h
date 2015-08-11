//
//  achievement.h
//  Taoquan_release
//
//  Created by lizhengyan on 15/8/9.
//
//

#ifndef __Taoquan_release__achievement__
#define __Taoquan_release__achievement__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Achievement : public Layer,public TableViewDelegate,TableViewDataSource{
public:
    virtual bool init();
    CREATE_FUNC(Achievement);
    Size visibleSize;
    Vec2 origin;
    void menuCloseCallback(Ref* pSender);
    Sprite* chengjiuBG;
    
    /* 必须实现的函数 */
    // 当滑动tableview时触发该方法 参数为当前的tableview对象
    virtual void scrollViewDidScroll(ScrollView* view) {};
    // 当tableview被放大或缩小时触发该方法  参数为当前tableview对象
    virtual void scrollViewDidZoom(ScrollView* view) {}
    // 当cell被点击时调用该方法 参数为当前的tableview对象与被点击的cell对象
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    // 设置tableview的Cell大小
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    // 获取编号为idx的cell
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    // 设置tableview中cell的个数
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
private:
    void michengCallback(Ref* pSender);
    void xinkongCallback(Ref* pSender);
    
//    TableView* chengjiu_view;
    
    
};

#endif /* defined(__Taoquan_release__achievement__) */
