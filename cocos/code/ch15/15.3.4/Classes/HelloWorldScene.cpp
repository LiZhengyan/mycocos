#include "HelloWorldScene.h"

USING_NS_CC;

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

	auto pItmLabel1 =  Label::createWithBMFont("fonts/fnt8.fnt", "Encoding Data");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu, this));

	Menu* mn = Menu::create(pItmMenu1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu(Ref* pSender)
{
	ValueVector listData ;

	auto createValueMap1 =[&](){
		ValueMap ret;
		ret["ID"] = Value(1);
		ret["CDate"] = Value("2014-3-10");
		ret["Content"] = "发布iOSBook0";
		ret["UserID"] = "tony";
		return ret;
	};
	listData.push_back(Value(createValueMap1()));

	auto createValueMap2 =[&](){
		ValueMap ret;
		ret["ID"] = Value(2);
		ret["CDate"] = Value("2014-3-11");
		ret["Content"] = "发布iOSBook1";
		ret["UserID"] = "tony";
		return ret;
	};
	listData.push_back(Value(createValueMap2()));

	auto createValueMap3 =[&](){
		ValueMap ret;
		ret["ID"] = Value(3);
		ret["CDate"] = Value("2014-3-12");
		ret["Content"] = "发布iOSBook2";
		ret["UserID"] = "tony";
		return ret;
	};

	listData.push_back(Value(createValueMap3()));

	auto createValueMap4 =[&](){
		ValueMap ret;
		ret["ID"] = Value(4);
		ret["CDate"] = Value("2014-3-13");
		ret["Content"] = "发布iOSBook3";
		ret["UserID"] = "tony";
		return ret;
	};
	listData.push_back(Value(createValueMap3()));

	auto createValueMap5 =[&](){
		ValueMap ret;
		ret["ID"] = Value(5);
		ret["CDate"] = Value("2014-3-14");
		ret["Content"] = "发布iOSBook4";
		ret["UserID"] = "tony";
		return ret;
	};

	auto createValueMap6  =[&](){
		ValueMap ret;
		ret["ID"] = Value(6);
		ret["CDate"] = Value("2014-3-15");
		ret["Content"] = "发布iOSBook5";
		ret["UserID"] = "tony";
		return ret;
	};

	auto parser = JsonParser::createWithArray(listData);
	parser->encode();
}
