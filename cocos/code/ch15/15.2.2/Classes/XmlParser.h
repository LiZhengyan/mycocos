//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef __XML_Parser_SCENE_H__
#define __XML_Parser_SCENE_H__

#include "cocos2d.h"

class XmlParser : public cocos2d::Ref, public cocos2d::SAXDelegator 
{
	//声明返回数据属性
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private: 

	std::string startElementName;//记录开始元素 
	cocos2d::ValueMap row;

public:
	
	static XmlParser * createWithFile(const char *fileName); 
   
    bool initWithFile(const char* xmlName); 
  
    //SAXDelegator 的3个回调方法
    virtual void startElement(void *ctx, const char *name, const char **atts); 
    virtual void endElement(void *ctx, const char *name); 
    virtual void textHandler(void *ctx, const char *ch, int len); 

};

#endif // __XML_Parser_SCENE_H__
