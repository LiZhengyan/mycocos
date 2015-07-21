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
#include"tinyxml2.h"

class XmlParser : cocos2d::Ref
{
	//声明返回数据属性
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private: 

	cocos2d::ValueMap row;

	//XML 内容
	std::string content;
public:

	static XmlParser * createWithFile(const char *fileName); 
    bool initWithFile(const char* xmlName); 

private: 
	void parse(); 

};

#endif // __XML_Parser_SCENE_H__
