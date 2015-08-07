//
//  SmartRes.h
//  TaoQuan2
//
//  Created by yongxinwan on 15/8/6.
//
//

#ifndef __TaoQuan2__SmartRes__
#define __TaoQuan2__SmartRes__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#define smartRes_dzty                   SmartRes::getInstance()->get_m_dzty()
#define smartRes_hiddenPicScale         SmartRes::getInstance()->get_hiddenPicScale()
#define smartRes_shuTiaoScale           SmartRes::getInstance()->get_shutiaocale()
#define smartRes_starHigh               SmartRes::getInstance()->get_starHight()
#define smartRes_shuZiHigh              SmartRes::getInstance()->get_shuZiHight()
#define smartRes_jinDuTiaoHeigh         SmartRes::getInstance()->get_jinDuTiaoHight()
#define smartRes_shangCiGuiJiHeigh      SmartRes::getInstance()->get_shangCiGuiJiHeigh()
#define smartRes_shiBaiTuichu           SmartRes::getInstance()->get_shiBaiTuichu()
#define smartRes_chengGongXiayiguan     SmartRes::getInstance()->get_chengGongXiayiguan()
class SmartRes : public Ref
{
public:
    static SmartRes*_instance;
    
    static SmartRes*getInstance();
    
    void setSmartResIpadAndMobilephone();//手机和iPad的适配
    
    void setAllMobilephoneResolution();//所有手机的分辨率适配
    
    void stop();
    SmartRes();
    ~SmartRes();
    
    float get_m_dzty(){
        return m_dzty;
    };
    float get_hiddenPicScale(){
        return hiddenPicScale;
    };
    float get_shutiaocale(){
        return shutiaocale;
    };
    float get_starHight(){
        return starHight;
    };
    float get_shuZiHight(){
        return shuZiHight;
    };
    float get_jinDuTiaoHight(){
        return jinDuTiaoHight;
    };
    float get_shangCiGuiJiHeigh(){
        return shangCiGuiJiHeigh;
    };
    float get_shiBaiTuichu(){
        return shiBaiTuichu;
    };
    float get_chengGongXiayiguan(){
        return chengGongXiayiguan;
    };

private:
    float m_dzty;
    float hiddenPicScale;
    float shutiaocale;
    float starHight;
    float shuZiHight;
    float jinDuTiaoHight;
    float shangCiGuiJiHeigh;
    
    float shiBaiTuichu;
    float chengGongXiayiguan;
};



#endif /* defined(__TaoQuan2__SmartRes__) */
