//
//  ResolvePicture.h
//  HelloWorld
//
//  Created by yongxinwan on 15/6/11.
//
//

#ifndef __HelloWorld__ResolvePicture__
#define __HelloWorld__ResolvePicture__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class ResolvePicture : public Sprite
{
public:
    static ResolvePicture* createResolvePicture();
    ~ResolvePicture();
    void initResolvePicture(const std::string& filename,int idNumber);
    void setPicturePosition(float x,float y);
    void changPicture(int level);
    
    int ID;
    std::string pictureColor;
    bool isCover;
    
};

#endif /* defined(__HelloWorld__ResolvePicture__) */
