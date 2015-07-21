//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef  _MY_NOTEDAO_H_
#define  _MY_NOTEDAO_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include <sqlite3.h>
#else
#include "sqlite3.h"
#endif

#include "MyUtility.h"

using namespace std;
USING_NS_CC;

class NoteDAO 
{
	sqlite3 *db;
public:

	//获得数据库文件路径
	static string dbDirectoryFile();

	//初始化数据库
	static int initDB();

	//插入Note方法
	static int create(string pDate, string pContent);

	//删除Note方法
	static int remove(string pDate);

	//修改Note方法
	static int modify(string pDate, string pContent);

	//查询所有数据方法
	static ValueVector findAll();

	//按照主键查询数据方法
	static ValueMap findById(string pDate);

};

#endif // _MY_NOTEDAO_H_
