//
//  chengjiu.cpp
//  Taoquan_release
//
//  Created by lizhengyan on 15/8/10.
//
//

#include "chengjiu.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
bool chengjiu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootlayer =CSLoader::createNode("Layer.csb");
    this->addChild(rootlayer);
    return true;
}