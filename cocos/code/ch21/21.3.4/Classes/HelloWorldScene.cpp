#include "HelloWorldScene.h"

///////////////////////////C 部分代码 开始//////////////////////////////////

//定义操作动作类型
typedef enum
{
	ACTION_QUERY				//查询操作
	,ACTION_REMOVE				//删除操作
	,ACTION_ADD					//添加操作
	,ACTION_MOD					//修改操作
} ActionTypes;

int action; //请求动作标识

//从服务器返回的JSON字符串
__String* returnJSONString;

int selectedRowId = -1;//选择行号

//服务器端返回的回调函数
size_t callback(void *ptr,size_t size,size_t number,void *stream)  
{  
	log("%s",ptr);
	std::string temp  = (char*)ptr;
	if (returnJSONString == NULL) {
		returnJSONString = __String::create(temp);
	} else {
		returnJSONString->append(temp);
	}
	return size * number;//这里一定要返回实际返回的字节数  
}  
///////////////////////////C 部分代码 结束//////////////////////////////////

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

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Insert Data");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "Delete Data");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(HelloWorld::OnClickMenu2, this));

	auto pItmLabel3 = Label::createWithBMFont("fonts/fnt8.fnt", "Update Data");
	auto pItmMenu3 = MenuItemLabel::create(pItmLabel3, CC_CALLBACK_1(HelloWorld::OnClickMenu3, this));

	auto pItmLabel4 = Label::createWithBMFont("fonts/fnt8.fnt", "Read Data");
	auto pItmMenu4 = MenuItemLabel::create(pItmLabel4, CC_CALLBACK_1(HelloWorld::OnClickMenu4, this));

	Menu* mn = Menu::create(pItmMenu1,pItmMenu2, pItmMenu3,pItmMenu4, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu1(Ref* pSender)
{
	returnJSONString = NULL;
	action = ACTION_ADD;
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=add&date=%s&content=%s","2014-4-1","tony insert data");

	this->httpRequest(param->getCString(), action);

}

void HelloWorld::OnClickMenu2(Ref* pSender)
{
	returnJSONString = NULL;
	action = ACTION_REMOVE;
	log("selectedRowId = %d", selectedRowId);
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=remove&id=%d", selectedRowId);

	this->httpRequest(param->getCString(), action);
}

void HelloWorld::OnClickMenu3(Ref* pSender)
{
	returnJSONString = NULL;
	action = ACTION_MOD;
	log("selectedRowId = %d", selectedRowId);
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=modify&id=%d&date=%s&content=%s", selectedRowId ,"2014-5-6","tom insert data");

	this->httpRequest(param->getCString(), action);
}

void HelloWorld::OnClickMenu4(Ref* pSender)
{
	returnJSONString = NULL;
	action = ACTION_QUERY;
	__String *param = __String::create("email=test@51work6.com&type=JSON&action=query");

	this->httpRequest(param->getCString(), action);

}

//HTTP Request
void HelloWorld::httpRequest(const char *param, int action)
{
	CURL *curl = curl_easy_init();

	if (curl) {

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param);  
		curl_easy_setopt(curl, CURLOPT_URL, BASE_URL);
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, callback);

		CURLcode res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		if (res == CURLE_OK) {

			ValueMap dict = JsonParser::decode(returnJSONString->getCString());			

			int intResultCode =  dict["ResultCode"].asInt();

			log("ResultCode = %d", intResultCode);

			if (intResultCode < 0) {
				char* errorStr;
				switch (intResultCode) {
				case -7:
					errorStr = "没有数据.";
					break;
				case -6:
					errorStr = "日期没有输入.";
					break;
				case -5:
					errorStr = "内容没有输入.";
					break;
				case -4:
					errorStr = "ID没有输入.";
					break;
				case -3:
					errorStr = "据访问失败.";
					break;
				case -2:
					errorStr = "您的账号最多能插入10条数据.";
					break;            
				case -1:
					errorStr = "用户不存在，请到http://iosbook3.com注册.";
				default:
					break;
				}
				log("Error Code %d  Error Message = %s", intResultCode, errorStr);
			} else {

				if (action == ACTION_QUERY) {

					ValueVector listData  = dict["Record"].asValueVector();

					for (auto& v: listData)
					{
						log("--------------------------");
						ValueMap row = v.asValueMap();

						log( "ID =%d \t CDate =%s \t Content =%s", 
							row["ID"].asInt(), 
							row["CDate"].asString().c_str(),
							row["Content"].asString().c_str());

						selectedRowId = row["ID"].asInt();
					}
				} else if(action == ACTION_ADD) {
					log("Insert the data successfully.");
				} else if(action == ACTION_REMOVE) {
					log("Delete the data successfully.");
				} else if(action == ACTION_MOD) {
					log("Modify the data successfully.");
				}
			}

		} else {
			log("code: %d",res);
		}
	} else {
		log("Initializing curl error.");
	} 
}
