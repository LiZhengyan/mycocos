//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

#include "JsonParser.h" 

#define BASE_URL "http://cocoagame.net/service/mynotes/WebService.php"

//定义操作动作类型
typedef enum
{
	ACTION_QUERY				//查询操作
	,ACTION_REMOVE				//删除操作
	,ACTION_ADD					//添加操作
	,ACTION_MOD					//修改操作
} ActionTypes;


class HelloWorld : public cocos2d::Layer
{
	int selectedRowId;			//选择行号
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	//Insert Data
	void OnClickMenu1(Ref* pSender);
	//Delete Data
	void OnClickMenu2(Ref* pSender);
	//Update Data
	void OnClickMenu3(Ref* pSender);
	//Read Data
	void OnClickMenu4(Ref* pSender);

	//HTTP Request
	void httpRequest(const char *param, int action);

	//Http Response Callback
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

};

#endif // __HELLOWORLD_SCENE_H__
