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
void ResolvePicture::changPicture()
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
    this->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
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
        
    }),NULL)) ;
    
    
}

