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
class SmartRes
{
public:
    static float getSmartResM_dzty(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float m_dzty;
        if (target==kTargetIpad) {
            m_dzty=0.12;
        }else{
            m_dzty=0.095;
        }
        return m_dzty;
    }
    
    static float getSmartResHiddenPicScale(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float hiddenPicScale;
        if (target==kTargetIpad) {

            hiddenPicScale=0.045;
        }else{
            hiddenPicScale=0.045;
        }
        return hiddenPicScale;
    }
    static float getSmartResShuTiaoScale(){
        TargetPlatform target=Application::getInstance()->getTargetPlatform();
        float shutiaocale;
        if (target==kTargetIpad) {
            
            shutiaocale=0.04;
        }else{
            shutiaocale=0.06;
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
};


#endif
