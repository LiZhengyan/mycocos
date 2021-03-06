//
//  DataUtil.h
//  HelloWorld
//
//  Created by yongxinwan on 15/6/11.
//
//

#ifndef __HelloWorld__DataUtil__
#define __HelloWorld__DataUtil__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
using namespace std;

class DataUtil
{
public:
    //用来创建一个db数据库 db为数据库的名字
    static void initDB(const char *db);
    //用来判断表格是否存在
    static bool tableIsExist(string name);
    //用来创建一个表名为name的表格，创建时会先匹配时否有该表的存在如果存在则不创建
    static void createTable(string sql,string name);
    //用来删除一张表名为name的表格，删除时会先匹配是否有该表的存在如果不存在则不执行删除操作
    static void deleteTable(string sql,string name);
    //用来向表中插入一条数据
    static void insertData(string sql);
    //用来向表中删除一条数据
    static void deleteData(string sql);
    //修改用户表的时间数据
    static void updateTimeData( int columnTime, int level);
    //修改用户表的是否锁
    static void updateSuoData( bool columnSuo, int level);
    //修改用户表的星星的数量
    static void updateStarData( int columnStarNum, int level);
    //修改用户表的是否存档
    static void updateIsFileData( bool columnIsFile, int level);
    
    //修改道具表的数据
    static void updatePropData( string column, int number);
    
    //获取一个记录的条数
    static int getDataCount(string sql);
    //读取一条记录的信息
    static void getDataInfo(string sql,cocos2d::Sprite *pSend);
    
    static cocos2d::Value getRow(std::string sql);
    static cocos2d::Value getAll(std::string sql);
    //关闭打开的数据库
    static void closeDB();
    
    static std::string getBigPicture(std::string dataName,int level);
    static cocos2d::ValueVector getSmallPicture(std::string dataName,int level);
    
protected:
    //int isExisted( void * para, int n_column, char ** column_value, char ** column_name );
private:
};
#endif /* defined(__HelloWorld__DataUtil__) */
