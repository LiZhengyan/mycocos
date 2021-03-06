//
//  IOSiAP_Bridge.cpp
//  LongChengDaRen
//
//  Created by 白白 on 14-11-11.
//
//

#include "IOSiAP_Bridge.h"
#include "cocos2d.h"
//#include "CommonInclude.h"
//#include "UpdateCoins.h"
USING_NS_CC;
using namespace std;

IOSiAP_Bridge::IOSiAP_Bridge()
{
    iap = new IOSiAP();
    iap->delegate = this;
}

IOSiAP_Bridge::~IOSiAP_Bridge()
{
    delete iap;
}

void IOSiAP_Bridge:: requestProducts(int id)
{
    productID = id;
    vector<std::string> product;
    product.push_back("taoquanRelease_buy_05");
//    product.push_back("renminbi6");
//    product.push_back("renminbi18");
//    product.push_back("renminbi50");
	//把需要付费的道具的所有product id都放到容器里面传进去
    iap->requestProducts(product);
}

void IOSiAP_Bridge::onRequestProductsFinish(void)
{
    std::string identifier = "";
    switch (productID) {
        case 6:
            identifier = "taoquanRelease_buy_05";
            break;
        case 18:
            identifier = "renminbi186";
            break;
        case 50:
            identifier = "renminbi50";
            break;
        case 98:
            identifier = "renminbi98";
            break;
        default:
            break;
    }

    //必须在onRequestProductsFinish后才能去请求iAP产品数据。
    IOSProduct *product = iap->iOSProductByIdentifier(identifier);
    // 然后可以发起付款请求。,第一个参数是由iOSProductByIdentifier获取的IOSProduct实例，第二个参数是购买数量
    iap->paymentWithProduct(product, 1);
}

void IOSiAP_Bridge::onRequestProductsError(int code)
{
    //这里requestProducts出错了，不能进行后面的所有操作。
    log("付款失败");
}

void IOSiAP_Bridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    
    if (event == IOSIAP_PAYMENT_PURCHAED) {
        log("恭喜你买了！！！");
        //付款成功了，可以吧金币发给玩家了。
		//根据传入的参数就能知道购买的是哪种类型的金币
        switch (productID) {
            case 6:
                
                break;
            case 18:
               
                break;
            case 50:
               
                break;
            case 98:
               
                break;
            default:
                break;
        }        
        log("付款成功");
        
    }
    //其他状态依情况处理掉。
}
