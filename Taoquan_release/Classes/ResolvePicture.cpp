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
void ResolvePicture::changPicture(int level)
{
    /*this->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
     //套中后更换图片
     int randN;
     do {
     randN=random(1, 6);
     } while (randN==this->ID);
     char name[20];
     sprintf(name, "gamescene/%d.png",randN);
     Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
     this->setTexture(texture);
     this->ID=randN;
     
     }),NULL)) ;*/
    int picMax=0;int picMin=0;
    if (level<=18) {
        picMax=16;
        picMin=11;
    }else{
        picMax=39;
        picMin=31;
    }
    
    this->runAction(Sequence::create(CallFunc::create([=](){
        //套中后更换图片
        int randN;
        do {
            randN=random(picMin, picMax);
        } while (randN==this->ID);
        char name[20];
        sprintf(name, "gamescene/%d.png",randN);
        Texture2D* texture = TextureCache::sharedTextureCache()->addImage(name);
        this->setTexture(texture);
        this->ID=randN;
        
    }),NULL)) ;
    
    
}

