//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//

#ifndef __BLayer_H__
#define __BLayer_H__

#include "cocos2d.h"

class  SceneBDelegator
{
public:
    virtual ~SceneBDelegator() {}
	//回调委托对象
    virtual void callBack(void *ctx, const char *str) = 0;
};

class BLayer : public cocos2d::Layer
{	
    SceneBDelegator*    _delegator;
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	// 更新单例对象状态.
	void menUpdate(cocos2d::Ref* pSender);

	// 返回上一个场景.
	void menReturnPreviousScene(cocos2d::Ref* pSender);
	
	void setDelegator(SceneBDelegator* delegator);

	// implement the "static create()" method manually
	CREATE_FUNC(BLayer);

};

#endif // __BLayer_H__
