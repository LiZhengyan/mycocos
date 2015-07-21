//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//

#ifndef __ALayer_SCENE_H__
#define __ALayer_SCENE_H__

#include "cocos2d.h"
#include "SceneB.h"

class ALayer : public cocos2d::Layer ,public SceneBDelegator
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance Vec2er
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // 进入下一个场景.
    void menEnterNextScene(cocos2d::Ref* pSender);
    
	virtual void callBack(void *ctx, const char *str);
	
	// implement the "static create()" method manually
    CREATE_FUNC(ALayer);
};

#endif // __ALayer_SCENE_H__
