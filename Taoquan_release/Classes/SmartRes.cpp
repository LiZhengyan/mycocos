//
//  SmartRes.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/8/6.
//
//

#include "SmartRes.h"
SmartRes* SmartRes::_instance = nullptr;
SmartRes* SmartRes::getInstance()
{
    
    if (_instance==nullptr)
    {
        _instance = new SmartRes();
    }
    return _instance;
    
}
SmartRes::SmartRes()
{
    setSmartResIpadAndMobilephone();
}

SmartRes::~SmartRes()
{
    
}


void SmartRes::setSmartResIpadAndMobilephone()
{
    TargetPlatform target=CCApplication::getInstance()->getTargetPlatform();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (target==kTargetIpad) {
        m_dzty=0.21;
        hiddenPicScale=0.08;
        shutiaocale=0.04;
        starHight=0.055;
        shuZiHight=0.605;
        jinDuTiaoHight=0.34;
        shangCiGuiJiHeigh=0.65;
        shiBaiTuichu=0.40;
        chengGongXiayiguan=0.40;
    }else{
        float hw=visibleSize.height/visibleSize.width;
        
        if (hw>1.6&&hw<1.7) {
            m_dzty=0.16;
            hiddenPicScale=0.08;
            shutiaocale=0.06;
            starHight=0.045;
            shuZiHight=0.615;
            jinDuTiaoHight=0.30;
            shangCiGuiJiHeigh=0.85;
            shiBaiTuichu=0.40;
            chengGongXiayiguan=0.40;
        }else if(hw>1.7&&hw<1.8){
            m_dzty=0.16;
            hiddenPicScale=0.08;
            shutiaocale=0.06;
            starHight=0.045;
            shuZiHight=0.615;
            jinDuTiaoHight=0.30;
            shangCiGuiJiHeigh=0.85;
            shiBaiTuichu=0.40;
            chengGongXiayiguan=0.40;
        }else if ((visibleSize.height/visibleSize.width)==1.500000){
            m_dzty=0.19;
            hiddenPicScale=0.08;
            shutiaocale=0.05;
            starHight=0.045;
            shuZiHight=0.61;
            jinDuTiaoHight=0.30;
            shangCiGuiJiHeigh=0.71;
            shiBaiTuichu=0.40;
            chengGongXiayiguan=0.40;
        }else{
            log("%f",visibleSize.height/visibleSize.width);
            m_dzty=0.16;
            hiddenPicScale=0.08;
            shutiaocale=0.06;
            starHight=0.045;
            shuZiHight=0.615;
            jinDuTiaoHight=0.30;
            shangCiGuiJiHeigh=0.85;
            shiBaiTuichu=0.38;
            chengGongXiayiguan=0.38;
        }
        
    }

}

void SmartRes::setAllMobilephoneResolution()
{}

void SmartRes::stop() {
    CC_SAFE_DELETE(_instance );
}