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

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

class JsonParser : public cocos2d::Ref
{
private: 
	cocos2d::ValueVector listData;

	std::string content;
public:

	static JsonParser * createWithArray(cocos2d::ValueVector pListData); 

	bool initWithArray(cocos2d::ValueVector pListData); 

	void encode(); 
};

#endif // __JSON_Parser_SCENE_H__
