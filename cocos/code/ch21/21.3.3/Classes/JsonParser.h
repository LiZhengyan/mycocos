//
//  Created by 关东升 on 2014-5-18.
//  本书网站：http://www.cocoagame.net
//  智捷iOS课堂在线课堂：http://v.51work6.com
//  智捷iOS课堂新浪微博：http://weibo.com/u/3215753973
//  作者微博：http://weibo.com/516inc
//  QQ：1575716557 邮箱：jylong06@163.com
//  QQ交流群：389037167/327403678
//


#ifndef __JSON_Parser_SCENE_H__
#define __JSON_Parser_SCENE_H__

#include "cocos2d.h"

//rapidjson 需要
#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

class JsonParser : public cocos2d::Ref
{
	//声明返回数据属性
	CC_SYNTHESIZE(cocos2d::ValueVector, list, List);

private: 
	cocos2d::ValueMap row;

	//JSON文件内容
	std::string content;
public:

	static JsonParser * createWithFile(const char *fileName); 
    
    bool initWithFile(const char* JSONName); 
	
	void decode(); 
};

#endif // __JSON_Parser_SCENE_H__
