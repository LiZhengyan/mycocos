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
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//贴图的纹理图片宽高必须是2的n次幂，128x128
	auto bg = Sprite::create("BackgroundTile.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	//贴图的纹理参数，水平重复平铺，垂直重复平铺
	Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
	bg->getTexture()->setTexParameters(tp);
	bg->setPosition(origin + Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(bg, 0);

	auto ball = Sprite::create("Ball.png");
	ball->setPosition(origin+Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(ball, 10, kBall_Tag);

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("HelloWorld onEnter");

	setAccelerometerEnabled(true);
}

void HelloWorld::onAcceleration(Acceleration* acc, Event *unused_event)
{
    log("{x = %f, y = %f}", acc->x,acc->y);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* ball = (Sprite*)this->getChildByTag(kBall_Tag);
    Size s = ball->getContentSize();
    Vec2 p0 = ball->getPosition();
    
    float p1x =  p0.x + acc->x * SPEED ;
    if ((p1x - s.width/2) <0) {
        p1x = s.width/2;
    }
    if ((p1x + s.width / 2) > visibleSize.width) {
        p1x = visibleSize.width - s.width / 2;
    }
    
    float p1y =  p0.y + acc->y * SPEED ;
    if ((p1y - s.height/2) < 0) {
        p1y = s.height/2;
    }
    if ((p1y + s.height/2) > visibleSize.height) {
        p1y = visibleSize.height - s.height/2;
    }
    ball->runAction(Place::create(Vec2( p1x, p1y))); 

}

void HelloWorld::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
}