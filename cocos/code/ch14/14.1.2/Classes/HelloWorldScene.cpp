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
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Test ResourcesDir Info");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "Test WritablePath Info");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(HelloWorld::OnClickMenu2, this));

	auto pItmLabel3 = Label::createWithBMFont("fonts/fnt8.fnt", "Read File");
	auto pItmMenu3 = MenuItemLabel::create(pItmLabel3, CC_CALLBACK_1(HelloWorld::OnClickMenu3, this));

	auto pItmLabel4 = Label::createWithBMFont("fonts/fnt8.fnt", "Write File");
	auto pItmMenu4 = MenuItemLabel::create(pItmLabel4, CC_CALLBACK_1(HelloWorld::OnClickMenu4, this));

	Menu* mn = Menu::create(pItmMenu1,pItmMenu2, pItmMenu3,pItmMenu4,  NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu1(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string fullPathForFilename = sharedFileUtils->fullPathForFilename("test.txt");
	log("fullPathForFilename path = %s", fullPathForFilename.c_str());

	bool isExist = false;
	isExist = sharedFileUtils->isFileExist("test.txt");
	log("%s",isExist ? "test.txt exists" : "test.txt doesn't exist");

}

void HelloWorld::OnClickMenu2(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string writablePath = sharedFileUtils->getWritablePath();
	log("writablePath = %s", writablePath.c_str());
}

void HelloWorld::OnClickMenu3(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string fullPathForFilename = sharedFileUtils->fullPathForFilename("test.txt");
	log("test.txt path = %s", fullPathForFilename.c_str());

	Data data = sharedFileUtils->getDataFromFile(fullPathForFilename);
	//Data构建string
	std::string content1 = std::string((const char*)data.getBytes(),0,data.getSize());
	log("content1 : %s",content1.c_str()); 
	std::string content2 = sharedFileUtils->getStringFromFile(fullPathForFilename);
	log("content2 : %s",content2.c_str()); 
}

void HelloWorld::OnClickMenu4(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
    //std::string ret;
    
    std::string writablePath = sharedFileUtils->getWritablePath();
    std::string fileName = writablePath+"test.txt";
    char szBuf[100] = "Testing Write to file.";
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp)
    {
        size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
        fclose(fp);
        if (ret != 0)
            log("Writing file to  path succeed.");
    }
}