#include "Particledemo.h"

using namespace cocos2d;
CCScene* Particledemo::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        Particledemo *layer = Particledemo::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}

bool Particledemo::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(Particledemo::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);
		//-new-//
		CCSize mysize=CCDirector::sharedDirector()->getWinSize();
		//CCParticleExplosion特效
		//创建CCParticleExplosion特效
        CCParticleSystem * p1=CCParticleExplosion::create();
		//设置特效贴图
		p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("5.png"));
		//设置自动释放
		p1->setAutoRemoveOnFinish(true);
        p1->setScale(2.0);
		//设置移动类型
		p1->setPositionType(kCCPositionTypeGrouped);
		//设置位置
		p1->setPosition(ccp(mysize.width/2,mysize.height/2));
		//添加特效
		this->addChild(p1);

		////CCParticleExplosion特效
		//CCParticleSystem * p2=CCParticleFire::create();
		//p2->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p2->setAutoRemoveOnFinish(true);
		//this->addChild(p2);

		////CCParticleFlower特效
		//CCParticleSystem * p3=CCParticleFlower::create();
		////p3->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p3->setAutoRemoveOnFinish(true);
		//this->addChild(p3);

		////CCParticleFireworks特效
		//CCParticleSystem * p4=CCParticleFireworks::create();
		////p4->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p4->setAutoRemoveOnFinish(true);
		//this->addChild(p4);

		////CCParticleGalaxy特效
		//CCParticleSystem * p5=CCParticleGalaxy::create();
		////p5->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p5->setAutoRemoveOnFinish(true);
		//this->addChild(p5);

		////CCParticleMeteor特效
		//CCParticleSystem * p6=CCParticleMeteor::create();
		////p6->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p6->setAutoRemoveOnFinish(true);
		//this->addChild(p6);

		////CCParticleRain特效
		//CCParticleSystem * p7=CCParticleRain::create();
		////p7->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p7->setAutoRemoveOnFinish(true);
		//this->addChild(p7);

		////CCParticleSmoke特效
		//CCParticleSystem * p8=CCParticleSmoke::create();
		////p8->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p8->setAutoRemoveOnFinish(true);
		//this->addChild(p8);

		////CCParticleSnow特效
		//CCParticleSystem * p9=CCParticleSnow::create();
		////p9->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p9->setAutoRemoveOnFinish(true);
		//this->addChild(p9);

		////CCParticleSpiral特效
		//CCParticleSystem * p10=CCParticleSpiral::create();
		////p10->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p10->setAutoRemoveOnFinish(true);
		//this->addChild(p10);

		////CCParticleSun特效
		//CCParticleSystem * p11=CCParticleSun::create();
		////p11->setTexture(CCTextureCache::sharedTextureCache()->addImage("t.jpg"));
		//p11->setAutoRemoveOnFinish(true);
		//this->addChild(p11);

		//自定义特效
//		CCParticleSystem * mypat=CCParticleSystemQuad::create("1.plist");
//		mypat->setPosition(ccp(mysize.width/2,mysize.height/2));
//		this->addChild(mypat);
		//-new-//
        bRet = true;
    } while (0);

    return bRet;
}

void Particledemo::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

