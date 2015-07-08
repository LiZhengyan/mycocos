//
//  MenuScene.h
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/8.
//
//

#ifndef __ctaoquan7__MenuScene__
#define __ctaoquan7__MenuScene__

#include <stdio.h>
#include <cocos2d.h>

class MenuScene: public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(MenuScene);
private:
    
    void menuItemSettingCallback(Ref* pSender);
    void menuItemHelpCallback(Ref* pSender);
    void menuItemStartCallback(Ref* pSender);
};


#endif /* defined(__ctaoquan7__MenuScene__) */
