#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d::network;

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

	Menu* mn = Menu::create(pItmMenu1,pItmMenu2, pItmMenu3,pItmMenu4, nullptr);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu1(Ref* pSender)
{
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=add&date=%s&content=%s","2014-4-1","tony insert data");

	this->httpRequest(param->getCString(), ACTION_ADD);

}

void HelloWorld::OnClickMenu2(Ref* pSender)
{
	log("selectedRowId = %d", selectedRowId);
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=remove&id=%d", selectedRowId);

	this->httpRequest(param->getCString(), ACTION_REMOVE);
}

void HelloWorld::OnClickMenu3(Ref* pSender)
{
	log("selectedRowId = %d", selectedRowId);
	__String *param = __String::createWithFormat("email=test@51work6.com&type=JSON&action=modify&id=%d&date=%s&content=%s", selectedRowId ,"2014-5-6","tom modify data");

	this->httpRequest(param->getCString(), ACTION_MOD);
}

void HelloWorld::OnClickMenu4(Ref* pSender)
{
	__String *param = __String::create("email=test@51work6.com&type=JSON&action=query");

	this->httpRequest(param->getCString(), ACTION_QUERY);

}

//HTTP Request
void HelloWorld::httpRequest(const char *param, int action)
{
	HttpRequest* request = new HttpRequest();
	request->setUrl(BASE_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));

	request->setRequestData(param, strlen(param)); 
	//获得请求标签
	__String *strTag = __String::createWithFormat("%d",action);
	request->setTag(strTag->getCString());

	HttpClient::getInstance()->send(request);
	request->release();
}

void HelloWorld::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	__String *strTag = __String::create(response->getHttpRequest()->getTag());
	int action = strTag->uintValue();
	log("request Action Code = %d",action);

	int statusCode = response->getResponseCode();

	log("response code: %d", statusCode);

	if (!response->isSucceed()) 
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *responseData = response->getResponseData();  
	std::string responseStr = std::string(responseData->begin(), responseData->end());

	ValueMap dict = JsonParser::decode(responseStr);			

	int intResultCode =  dict["ResultCode"].asInt();

	log("ResultCode = %d", intResultCode);

	if (intResultCode < 0) {
		char* errorStr = NULL;
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
			errorStr = "用户不存在，请到http://cocoagame.net注册.";
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
}
