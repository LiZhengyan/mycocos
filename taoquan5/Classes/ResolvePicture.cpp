//
//  ResolvePicture.cpp
//  HelloWorld
//
//  Created by yongxinwan on 15/6/11.
//
//

#include "ResolvePicture.h"
ResolvePicture* ResolvePicture::createResolvePicture()
{
    ResolvePicture* resolvePicture=new ResolvePicture();
    if (resolvePicture) {
        return resolvePicture;
    }
    return NULL;
}
ResolvePicture::~ResolvePicture()
{

}
void ResolvePicture::initResolvePicture(const std::string& filename,int idNumber)
{
    ID=idNumber;
    isCover=false;
    
    this->initWithFile(filename);
    
}

void ResolvePicture::setPicturePosition(float x,float y)
{
 
    this->setPosition(Vec2(x, y));
}