//
//  Created by �ض��� on 2014-5-18.
//  ������վ��http://www.cocoagame.net
//  �ǽ�iOS�������߿��ã�http://v.51work6.com
//  �ǽ�iOS��������΢����http://weibo.com/u/3215753973
//  ����΢����http://weibo.com/516inc
//  QQ��1575716557 ���䣺jylong06@163.com
//  QQ����Ⱥ��389037167/327403678
//


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
