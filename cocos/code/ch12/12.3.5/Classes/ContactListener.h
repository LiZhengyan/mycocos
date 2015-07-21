//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//



#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class ContactListener : public b2ContactListener
{
private:
	//两个物体开始接触时会响应
	virtual void BeginContact(b2Contact* contact);

	//持续接触时响应
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//持续接触时响应，调用完preSolve后调用
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	
	//分离时响应
	virtual void EndContact(b2Contact* contact);

};