//
//  LevelData.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/6/30.
//
//

#ifndef __TaoQuan2__LevelData__
#define __TaoQuan2__LevelData__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
class LevelData
{
public:
    //解析Json
    //测试
    void makeXml(const char * fileName);
    
    
    static Value paeseXml(int level);
    static Value paeseLevelSmallPicture(int level);
    static Value paeseLevelShape(int randNum);
};


#endif /* defined(__TaoQuan2__LevelData__) */
