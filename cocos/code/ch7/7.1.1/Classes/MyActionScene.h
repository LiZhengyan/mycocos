//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef __MYACTION_SCENE_H__
#define __MYACTION_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

class MyAction : public cocos2d::Layer
{
	bool hiddenFlag;
    cocos2d::Sprite *sprite;

public:
	
	static cocos2d::Scene* createScene();
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(MyAction);
	
	// a selector callback
    void goMenu(cocos2d::Ref* pSender);
    void backMenu(cocos2d::Ref* pSender);
};

#endif // __MYACTION_SCENE_H__
