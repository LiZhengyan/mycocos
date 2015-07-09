//
//  Setting.h
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/8.
//
//

#ifndef __ctaoquan7__Setting__
#define __ctaoquan7__Setting__

#include <stdio.h>
#include "cocos2d.h"

class Setting: public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    ~Setting(void);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
private:
    
    CREATE_FUNC(Setting);
    void menuOkCallback(Ref*pSender);
    void menuSoundToggleCallback(Ref*pSender);
    void menuMusicToggleCallback(Ref*pSender);
    void menuCallback(Ref* pSender);

};


#endif /* defined(__ctaoquan7__Setting__) */
