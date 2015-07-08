#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
    Vector<Sprite *> list;
    
    __Dictionary* dict1;
    __Dictionary* dict2;
    
    Map<std::string, Sprite*> map1;
    Map<std::string, Sprite*> map2;
    
    cocos2d::ValueVector vlist;
    cocos2d::ValueMap   mlist;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    ~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void clickstartGame(Ref * Psender);
    void menucloseCallBack(Ref* pSender);
    void clickstartGame3(Ref *Psender);
};

#endif // __HELLOWORLD_SCENE_H__
