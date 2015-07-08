//
//  XMLParser.h
//  ctaoquan5
//
//  Created by lizhengyan on 15/6/30.
//
//

#ifndef ctaoquan5_XMLParser_h
#define ctaoquan5_XMLParser_h



#include <string>
#include "cocos2d.h"

class XMLParser : public cocos2d::Ref, public cocos2d::SAXDelegator
{
public:
    static XMLParser* parseWithFile(const char *xmlFileName);
    
    static XMLParser* parseWithString(const char *content);
    
    XMLParser();
    virtual ~XMLParser();
    
    //从本地xml文件读取
    bool initWithFile(const char *xmlFileName);
    //从字符中读取，可用于读取网络中的xml数据
    bool initWithString(const char *content);
    
    //对应xml标签开始,如：<string name="app_name">
    virtual void startElement(void *ctx, const char *name, const char **atts);
    
    //对应xml标签结束,如：</string>
    virtual void endElement(void *ctx, const char *name);
    
    //对应xml标签文本
    virtual void textHandler(void *ctx, const char *s, int len);
    
    cocos2d::CCString* getString(const char *key);
    
private:
    cocos2d::CCDictionary *m_pDictionary;
    std::string m_key;
    
    std::string startXMLElement;
    std::string endXMLElement;
    
};

#endif
