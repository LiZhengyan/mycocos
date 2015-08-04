void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    //暂停指针的旋转动作
    Director* director=Director::getInstance();
    director->getActionManager()->resumeTarget(GameScene::_spriteTiao);
    director->getActionManager()->resumeTarget(GameScene::_dottedSprite);//暂停虚线的动作
    //director->getActionManager()->addAction(_repeatLineBG, _dottedLineProgress, false);
    
    //RepeatForever* repeatLineBG=(RepeatForever*)_powerProgress->getActionByTag(1000);
    _powerProgress->setVisible(false);//显示指针的进度条
    //_dottedSprite->setVisible(true);
    _dottedLineProgress->setVisible(false);
    
    if (_isTouch) {
        float rr=sqrt(visibleSize.width/2*visibleSize.width/2+visibleSize.height*9/10*visibleSize.height*9/10);
        float r=_powerProgress->getPercentage()*0.01*rr;
        
        if (_spriteTiao->getRotation()>0) {
            
            float x1=r*cos((90-_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90-_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/10;
            x=x1+visibleSize.width/2;
        }else{
            float x1=r*cos((90+_spriteTiao->getRotation())*3.1415926/180);
            float y1=r*sin((90+_spriteTiao->getRotation())*3.1415926/180);
            if (y1<0) {
                y1=-y1;
            }
            y=y1+visibleSize.height/10;
            x=visibleSize.width/2-x1;
        }
        float s=sqrtf((x*x+y*y)-(_spriteQuan->getPositionX()*getPositionX()+getPositionY()*getPositionY()));
        _isTouch=false;
        
        
        log("S=%f",s);
        
        ResolvePicture* taozhong=NULL;
        ResolvePicture* taozhong_heshi=NULL;
        for (int i=0; i<spriteVector.size(); i++)
        {
            //判断是否套住
            ResolvePicture* showRp=spriteVector.at(i);
            if (sqrt((x-showRp->getPositionX())*(x-showRp->getPositionX())+(y-showRp->getPositionY())*(y-showRp->getPositionY()))<=53.0)
            {
                taozhong=showRp;
                showRp->isCover=true;
                for (int j=0; j<hiddenPictureVector.size(); j++) {
                    ResolvePicture* hiddenRp=hiddenPictureVector.at(j);
                    if (hiddenRp->ID==showRp->ID)
                    {
                        taozhong_heshi=hiddenRp;
                    }
                }
            }
        }
        
        
        
        auto menuItemBlink=Spawn::create(FadeTo::create(0.6f, 0), NULL);    //套中目标以后，块逐渐消失
        auto spriteQuan_return  = TargetedAction::create(_spriteQuan,Place::create(Vec2(visibleSize.width/2, visibleSize.height*0.1)));  //圈子瞬移回来
        auto targetAct = TargetedAction::create(taozhong,menuItemBlink);  //绑定
        
        
        
        if(taozhong != NULL && taozhong_heshi!=NULL)       //套中了，并且是所需要的块
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(taozhong->getPositionX(),taozhong->getPositionY()));  //替换目标point
            //圈子一边飞一边变变形
            auto quanRate = Spawn::create(quanMove,   Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA,QUAN_SCA*0.5), NULL),  NULL);
            auto ease=EaseSineOut::create(quanRate);
            
            //            2个特效p4p5，只要套中，且套对才又
            ParticleSystem * p4=ParticleGalaxy::createWithTotalParticles(200);
            p4->setPosition(Vec2(taozhong->getPositionX(),taozhong->getPositionY()+50));
            p4->setStartColor(Color4F(1,1,1,1));
            this->addChild(p4,5);
            p4->setVisible(false);
            
            
            auto p5 = MotionStreak::create(0.2, 1, 100, Color3B::WHITE,"start5.png" );
            p5->setPosition(Vec2(taozhong->getPositionX(),taozhong->getPositionY()+50));
            p5->setVisible(false);
            p5->isFastMode();
            this->addChild(p5,5);
            
            
            _spriteQuan->runAction(Sequence::create(ease,
                                                    CallFunc::create([=]{_spriteQuan->setZOrder(1);}),    //设置圈子的zorder
                                                    MoveBy::create(0.3, Vec2(0,-30)),  //下沉
                                                    FadeTo::create(0.2, 0),
                                                    targetAct,   //套中的块在做动作
                                                    spriteQuan_return,    //回来吧圈子
                                                    CallFunc::create([=]{_spriteQuan->setZOrder(3);}),    //恢复圈子的zorder原来的
                                                    CallFunc::create([=](){_spriteQuan->setOpacity(255);_spriteQuan->setScale(QUAN_SCA);_spriteQuan->setRotation(0);
                p4->setVisible(true);
                p5->setVisible(true);
                //                                                                            特效飞到左下角
                p4->runAction(MoveTo::create(0.5, taozhong_heshi->getPosition()));
                p5->runAction(MoveTo::create(0.5, taozhong_heshi->getPosition()));
                taozhong->changPicture(cLevel);  //替换图片
                
                
                
            }),
                                                    
                                                    DelayTime::create(0.5), //等p4结束哦 0.5秒
                                                    CallFunc::create([=](){taozhong->setVisible(true);taozhong->setOpacity(255);
                //                                                                            taozhong_heshi->setVisible(false);
                addChild(taozhong_heshi,3);
                taozhong_heshi->setOpacity(0);
                hiddenPictureVector.eraseObject(taozhong_heshi);
                showPictureVector.pushBack(taozhong_heshi);
                taozhong_heshi->runAction(FadeTo::create(0.5, 255));
                removeChild(p4,p5);if(--_loopNumber>0){_isTouch=true;}}),
                                                    NULL));
        }else if (taozhong != NULL)
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(taozhong->getPositionX(),taozhong->getPositionY()));
            auto quanRate = Spawn::create(quanMove, Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA*0.8,QUAN_SCA*0.56), NULL), NULL);
            auto ease=EaseSineOut::create(quanRate);
            
            auto targetAct = TargetedAction::create(taozhong,Sequence::create(MoveBy::create(0.05, Vec2(-15,0)),MoveBy::create(0.1, Vec2(30,0)), MoveBy::create(0.05, Vec2(-15,0)),NULL));
            _spriteQuan->runAction(Sequence::create(ease,
                                                    CallFunc::create([=]{_spriteQuan->setZOrder(1);}),
                                                    MoveBy::create(0.3, Vec2(0,-30)),
                                                    FadeTo::create(0.2, 0),spriteQuan_return,
                                                    CallFunc::create([=]{_spriteQuan->setZOrder(3);}),
                                                    Repeat::create(targetAct,1),
                                                    CallFunc::create([=](){_spriteQuan->setOpacity(255);_spriteQuan->setScale(QUAN_SCA);_spriteQuan->setRotation(0);
                taozhong->setPosition(taozhong->getPositionX(),taozhong->getPositionY());
                _spriteQuan->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.1));if(--_loopNumber>0){_isTouch=true;}
            }),NULL));
        }else
        {
            MoveTo* quanMove=MoveTo::create(s/(visibleSize.width*1.3), Vec2(x, y));
            auto quanRate = Spawn::create(quanMove,  Sequence::create(ScaleTo::create((s/(visibleSize.width*1.3)*1),QUAN_SCA*0.8,QUAN_SCA*0.56), NULL),NULL);
            auto ease=EaseSineOut::create(quanRate);
            
            _spriteQuan->runAction(Sequence::create(ease,
                                                    //                                                    CallFunc::create([=]{p6->setVisible(false);}),
                                                    FadeTo::create(0.2, 0),spriteQuan_return,CallFunc::create([=](){
                _spriteQuan->setOpacity(255);
                _spriteQuan->setRotation(0);
                _spriteQuan->setScale(QUAN_SCA);
                if(--_loopNumber>0){_isTouch=true;}}),NULL));
            log("啥都没有中。回来吧");
            log("在循环里面圈子的数目是%d",_loopNumber);
            
            
        }
        log("-----End-------x= %f y=%f ",x,y);
    }
    if(_loopNumber==0){_isTouch=false;}
    
}