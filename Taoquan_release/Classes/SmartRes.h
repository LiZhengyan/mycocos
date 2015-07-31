//
//  SmartRes.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/7/8.
//
//

#ifndef TaoQuan2_SmartRes_h
#define TaoQuan2_SmartRes_h
#include "cocos2d.h"
USING_NS_CC;
#define smartRes_dzty                   SmartRes::getSmartResM_dzty()
#define smartRes_hiddenPicScale         SmartRes::getSmartResHiddenPicScale()
#define smartRes_shuTiaoScale           SmartRes::getSmartResShuTiaoScale()
#define smartRes_starHigh               SmartRes::getSmartResSatrHight()
#define smartRes_shuZiHigh              SmartRes::getSmartShuZiHight()
#define smartRes_jinDuTiaoHeigh         SmartRes::getSmartJinDuTiaoHeigh()
#define smartRes_shangCiGuiJiHeigh      SmartRes::getSmartShangCiGuiJiHeigh()

class SmartRes
{
public:
    int level=UserDefault::getInstance()->getIntegerForKey("comeInLevel");
    static float getSmartResM_dzty(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float m_dzty;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        int height=(int)visibleSize.height;
        if (height==960) {
             m_dzty=0.19;
        }else{
            if (target==kTargetIpad) {
                m_dzty=0.21;
            }else{
                m_dzty=0.16;
            }
        }
        return m_dzty;
    }
    
    static float getSmartResHiddenPicScale(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float hiddenPicScale;
        if (target==kTargetIpad) {

            hiddenPicScale=0.08;
        }else{
            hiddenPicScale=0.08;
        }
        return hiddenPicScale;
    }
    static float getSmartResShuTiaoScale(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float shutiaocale;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        int height=(int)visibleSize.height;
        if (height==960) {
            shutiaocale=0.05;
        }else{

            if (target==kTargetIpad) {
                shutiaocale=0.04;
            }else{
                shutiaocale=0.06;
            }
        }
        return shutiaocale;
    }
    static float getSmartResSatrHight(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float starHight;
        if (target==kTargetIpad) {
            
            starHight=0.055;
        }else{
            starHight=0.045;
        }
        return starHight;
    }
    static float getSmartShuZiHight(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float shuZiHight;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        int height=(int)visibleSize.height;
        if (height==960) {
            shuZiHight=0.61;
        }else{
            if (target==kTargetIpad) {
                shuZiHight=0.605;
            }else{
                shuZiHight=0.615;
            }
        }
        return shuZiHight;
    }
    static float getSmartJinDuTiaoHeigh(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float jinDuTiaoHight;
        if (target==kTargetIpad) {
            jinDuTiaoHight=0.34;
        }else{
            jinDuTiaoHight=0.30;
        }
        return jinDuTiaoHight;
    }
    static float getSmartShangCiGuiJiHeigh(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float shangCiGuiJiHeigh;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        int height=(int)visibleSize.height;
        if (height==960) {
            shangCiGuiJiHeigh=0.71;
        }else{
            if (target==kTargetIpad) {
                shangCiGuiJiHeigh=0.65;
            }else{
                shangCiGuiJiHeigh=0.85;
            }
        }
        return shangCiGuiJiHeigh;
    }
   

};

#endif
