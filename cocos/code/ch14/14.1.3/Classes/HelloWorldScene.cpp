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

	auto pItmLabel1 = Label::createWithBMFont("fonts/fnt8.fnt", "Write File");
	auto pItmMenu1 = MenuItemLabel::create(pItmLabel1, CC_CALLBACK_1(HelloWorld::OnClickMenu1, this));

	auto pItmLabel2 = Label::createWithBMFont("fonts/fnt8.fnt", "Search File");
	auto pItmMenu2 = MenuItemLabel::create(pItmLabel2, CC_CALLBACK_1(HelloWorld::OnClickMenu2, this));

	Menu* mn = Menu::create(pItmMenu1,pItmMenu2, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::OnClickMenu1(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();
    std::string ret;
    
    sharedFileUtils->purgeCachedEntries();
    std::string writablePath = sharedFileUtils->getWritablePath();
    std::string fileName = writablePath+"test.txt";
    char szBuf[100] = "The file is in the resources directory";
    FILE* fp = fopen(fileName.c_str(), "wb");
    if (fp)
    {
        size_t ret = fwrite(szBuf, 1, strlen(szBuf), fp);
        fclose(fp);
        if (ret != 0)
            log("Writing file to  path succeed.");
    }
}

void HelloWorld::OnClickMenu2(Ref* pSender)
{
	auto sharedFileUtils = FileUtils::getInstance();    

    sharedFileUtils->purgeCachedEntries();

	std::vector<std::string> searchPaths = sharedFileUtils->getSearchPaths();
	std::string writablePath = sharedFileUtils->getWritablePath();

	searchPaths.insert(searchPaths.begin(), "dir1");
	searchPaths.insert(searchPaths.begin()+1, writablePath);
	sharedFileUtils->setSearchPaths(searchPaths);

	std::string fullPathForFilename = sharedFileUtils->fullPathForFilename("test.txt");
	log("test.txt 's fullPathForFilename is : %s",fullPathForFilename.c_str());

	Data data = sharedFileUtils->getDataFromFile(fullPathForFilename);
	std::string content = sharedFileUtils->getStringFromFile(fullPathForFilename);
	log("File content is : %s",content.c_str());

}