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

class Setting: public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(Setting);
private:
    void menuOkCallback(Ref*pSender);
    void menuSoundToggleCallback(Ref*pSender);
    void menuMusicToggleCallback(Ref*pSender);
};


#endif /* defined(__ctaoquan7__Setting__) */
