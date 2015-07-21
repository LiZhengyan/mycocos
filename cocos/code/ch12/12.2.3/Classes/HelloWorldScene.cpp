#include "HelloWorldScene.h"

USING_NS_CC;

//extern const char* PHYSICSCONTACT_EVENT_NAME;

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


void HelloWorld::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		if (spriteA && spriteA->getTag() == 1 
			&& spriteB && spriteB->getTag() == 1) 
		{
			spriteA->setColor(Color3B::YELLOW);
			spriteB->setColor(Color3B::YELLOW);
		}

		log("onContactBegin");
		return true;
	};	

	listener->onContactPreSolve = [] (PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{
		log("onContactPreSolve");
		return true;
	};

	listener->onContactPostSolve = [] (PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{
		log("onContactPostSolve");
	};

	listener->onContactSeperate = [](PhysicsContact& contact) 
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		if (spriteA && spriteA->getTag() == 1 
			&& spriteB && spriteB->getTag() == 1) 
		{
			spriteA->setColor(Color3B::WHITE);
			spriteB->setColor(Color3B::WHITE);
		}
		log("onContactSeperate");
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1); 


}

void HelloWorld::onExit()
{
	Layer::onExit();
	log("HelloWorld onExit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = touch->getLocation();
	addNewSpriteAtPosition(location);
	return false;
}	


void HelloWorld::addNewSpriteAtPosition(Vec2 p)
{    
	auto sp = Sprite::create("BoxA2.png");
	sp->setTag(1);
	auto body = PhysicsBody::createBox(sp->getContentSize());
	//body->setContactTestBitmask(0x1);
	//body->setCategoryBitmask(0x2);
	//body->setCollisionBitmask(0x2);

	sp->setPhysicsBody(body);	
	sp->setPosition(p);
	this->addChild(sp);
}
