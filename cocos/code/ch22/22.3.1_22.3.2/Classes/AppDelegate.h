//
//  Created by �ض��� on 2014-5-18.
//  ������վ��http://www.cocoagame.net
//  �ǽ�iOS�������߿��ã�http://v.51work6.com
//  �ǽ�iOS��������΢����http://weibo.com/u/3215753973
//  ����΢����http://weibo.com/516inc
//  QQ��1575716557 ���䣺jylong06@163.com
//  QQ����Ⱥ��389037167/327403678
//


#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

