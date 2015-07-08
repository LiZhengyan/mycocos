//
//  SelectLevel.h
//  TaoQuan
//
//  Created by yongxinwan on 15/6/16.
//
//

#ifndef __TaoQuan__SelectLevel__
#define __TaoQuan__SelectLevel__

#include <stdio.h>
#include "cocos2d.h"
#include "DataUtil.h"
USING_NS_CC;

class SelectLevel:public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(SelectLevel);
    void menuCloseCallback(Ref* pSender);
};

#endif /* defined(__TaoQuan__SelectLevel__) */
