//
//  DataUtil.cpp
//  HelloWorld
//
//  Created by yongxinwan on 15/6/11.
//
//

#include "DataUtil.h"
#include "sqlite3.h"
USING_NS_CC;

sqlite3 *pDB = NULL;//数据库指针
char * errMsg = NULL;//错误信息
std::string sqlstr;//SQL指令
int result;//sqlite3_exec返回值


//创建数据库
void DataUtil::initDB(const char *db )
{
    //打开一个数据库，如果该数据库不存在，则创建一个数据库文件
    //std::string filename = FileUtils::sharedFileUtils()->fullPathForFilename("test.db");
    //result = sqlite3_open(filename.c_str(), &pDB);
    std::string path=FileUtils::getInstance()->getWritablePath()+db;
    log( "数据库路径：%s\n" , path.c_str() );
    result = sqlite3_open(path.c_str(), &pDB);
    
    if( result != SQLITE_OK )
        log( "打开数据库失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
    else
        log("打开数据库成功");
    
    
    //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent();
}


//tableIsExist的回调函数
int isExisted( void * para, int n_column, char ** column_value, char ** column_name )
{
    bool *isExisted_=(bool*)para;
    *isExisted_=(**column_value)!='0';
    return 0;
}
//判断表格是否存在
bool DataUtil::tableIsExist( string name )
{
    if (pDB!=NULL)
    {
        //判断表是否存在
        bool tableIsExisted;
        sqlstr = "select count(type) from sqlite_master where type='table' and name ='"+name+"'";
        result =sqlite3_exec(pDB,sqlstr.c_str(),isExisted,&tableIsExisted,&errMsg);
        return tableIsExisted;
    }
    return false;
}


//在数据库中判断名为name的表示否存在，如果不存在则创建这张表
//@示例语句string sqls = "create table user(id integer,username text,password text)";
void DataUtil::createTable( string sql,string name )
{
    if (!tableIsExist(name))
    {
        //创建表，设置ID为主键，且自动增加
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        if( result != SQLITE_OK )
            log( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
    }else
    {
        log("表存在");
    }
    
}


//删除表格
//@示例语句sqlstr="drop table name";
void DataUtil::deleteTable( string sql,string name )
{
    if (tableIsExist(name))
    {
        result = sqlite3_exec(pDB,sql.c_str(),NULL,NULL,&errMsg);
        if( result != SQLITE_OK )
            log( "创建表失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
    }
}


//插入数据
//@示例语句sqlstr=" insert into MyTable_1( name ) values ( '擎天柱' ) ";
void DataUtil::insertData( string sql ){
    result = sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
}


//删除数据
//@示例语句sqlstr="delete from MyTable_1 where ID = 2";
void DataUtil::deleteData( string sql )
{
    result=sqlite3_exec( pDB, sql.c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
}


//修改数据
//@示例语句        sqlstr="update MyTable_1 set name='威震天' where ID = 3";
void DataUtil::updateTimeData( int columnTime, int level)
{
    
    std::stringstream str;
    str<<"update User"<<" set useTime="<< columnTime<< " WHERE level = " <<level<< "";
    result = sqlite3_exec( pDB, str.str().c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
}

void DataUtil::updateSuoData( bool columnSuo, int level)
{
    std::stringstream str;
    str<<"update User"<<" set isSuo="<< columnSuo<< " WHERE level = " <<level<< "";
    result = sqlite3_exec( pDB, str.str().c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );

}
void DataUtil::updateStarData( int columnStarNum, int level)
{
    std::stringstream str;
    str<<"update User"<<" set starNum="<< columnStarNum<< " WHERE level = " <<level<< "";
    result = sqlite3_exec( pDB, str.str().c_str() , NULL, NULL, &errMsg );
    if(result != SQLITE_OK )
        log( "插入记录失败，错误码:%d ，错误原因:%s\n" , result, errMsg );
}

//getDataCount的回调函数
int loadRecordCount( void * para, int n_column, char ** column_value, char ** column_name )
{
    int *count=(int*)para;
    *count=n_column;
    return 0;
}
//获取记录的条数
//@示例语句string sqlsssss = "select count(*) from user";
//@示例语句  取得表格字段的语句string sqlsssss = "select * from user";
int DataUtil::getDataCount( string sql )
{
    int count=0;
    sqlite3_exec( pDB, sql.c_str() , loadRecordCount, &count, &errMsg );
    
    return count;
}


//getDataInfo的回调函数
int loadRecord( void * para, int n_column, char ** column_value, char ** column_name )
{
    log("ID=%s,name=%s,level=%s, isCover=%s",column_value[0],column_value[1],column_value[2],column_value[3]);
    return 0;
}
//获取一条记录的信息 其中的pSend是一个实体类我们以后可以自定义一个继承了CCObject的类来代替他保存数据库中取出来的数据
void DataUtil::getDataInfo( string sql,Sprite *pSend )
{
    sqlite3_exec( pDB, sql.c_str() , loadRecord, NULL, &errMsg );
}

Value DataUtil::getRow(std::string sql){
    char **re;
    int r, c, res;
    char* errMsg;
    Value row;
    res = sqlite3_get_table(pDB, sql.c_str(), &re, &r, &c, &errMsg);
    if (res != SQLITE_OK){
        CCLOG("select table row failed, number:%d, msg:%s, sql:%s", res, errMsg, sql.c_str());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(errMsg, &res);
        return row;
    }
    ValueMap map;
    for (int j = 0; j<c; j++){
        std::string k(re[j]);
        Value v(re[c + j]);
        map[k] = v;
    }
    row = Value(map);
    return row;
}


Value DataUtil::getAll(std::string sql){
    char **re;
    int r, c, res;
    char* errMsg;
    ValueVector all;
    res = sqlite3_get_table(pDB, sql.c_str(), &re, &r, &c, &errMsg);
    if (res != SQLITE_OK){
        CCLOG("select table all failed, number:%d, msg:%s, sql:%s", res, errMsg, sql.c_str());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(errMsg, &res);
        return Value(all);
    }
    int i, j;
    ValueVector vec;
    for (i = 1; i <= r; i++){
        ValueMap map;
        for (j = 0; j<c; j++){
            std::string k(re[j]);
            Value v(re[i * c + j]);
            map[k] = v;
        }
        vec.push_back(Value(map));
    }
    sqlite3_free_table(re);
    all = vec;
    return Value(all);
}
//获取数据库中的大图
std::string DataUtil::getBigPicture(std::string dataName,int level)
{
    //std::string str("select * from ");
    //str+=dataName;
    //str+=" where level=";
    //str+=static_cast<int>(level);
    
    std::stringstream str;
    str<<"SELECT * FROM "<< dataName << " WHERE level = " <<level<< "";
    
    log("%s",str.str().c_str());
    //string bigPictureStr = "select * from bigPicture where level=1";
    //取出数据库的一行
    ValueMap bigVm=DataUtil::getRow(str.str()).asValueMap();
    std::string bigPicName=bigVm["name"].asString();
    
    return bigPicName;
    
}
//获取数据库中的小图
ValueVector DataUtil::getSmallPicture(std::string dataName,int level)
{
    std::string str("select * from ");
    str+=dataName;
    str+=" where level= ";
    str+=static_cast<int>(level);
    log("%s",str.c_str());
    //取出数据库的一行
    ValueVector avm=DataUtil::getAll(dataName).asValueVector();
    return avm;
    
}


//关闭数据库
void DataUtil::closeDB()
{
    sqlite3_close(pDB);
}