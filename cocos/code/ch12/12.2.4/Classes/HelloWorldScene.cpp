#include "HelloWorldScene.h"

USING_NS_CC;

extern const char* PHYSICSCONTACT_EVENT_NAME;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	PhysicsWorld* phyWorld = scene->getPhysicsWorld();
	phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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
	
	//定义世界的边界
	auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = touch->getLocation();
	addNewSpriteAtPosition(location);
	return false;
}	

void HelloWorld::addNewSpriteAtPosition(Vec2 p)
{    

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto boxA = Sprite::create("BoxA2.png");
	boxA->setPosition(origin+ p);

	auto boxABody = PhysicsBody::createBox(boxA->getContentSize());
	boxA->setPhysicsBody(boxABody);	
	addChild(boxA, 10, 100);

	auto boxB = Sprite::create("BoxB2.png");
	boxB->setPosition(origin + p + Vec2(0, -120));
	
	auto boxBBody = PhysicsBody::createBox(boxB->getContentSize());
	boxB->setPhysicsBody(boxBBody);	
	addChild(boxB, 20, 101);

	auto world = this->getScene()->getPhysicsWorld();

	PhysicsJointDistance* joint = PhysicsJointDistance::construct(boxABody, boxBBody, 
		Vec2(0, 0), Vec2(0, boxB->getContentSize().width / 2));

	world->addJoint(joint);

}
