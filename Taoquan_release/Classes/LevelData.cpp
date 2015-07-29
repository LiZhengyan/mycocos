//
//  LevelData.cpp
//  TaoQuan2
//
//  Created by yongxinwan on 15/6/30.
//
//

#include "LevelData.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace rapidjson;

USING_NS_CC;
cocos2d::Value LevelData::paeseXml(int level)
{
    ValueVector vvAll;
    ValueVector vv;
    std::string load_str;
    load_str = cocos2d::FileUtils::getInstance()->getStringFromFile("myhero.json");
    rapidjson::Document readdoc;
    readdoc.Parse<0>(load_str.c_str());
    if(readdoc.HasParseError())
    {
        CCLOG("GetParseError%s\n", readdoc.GetParseError());
    }
    
    rapidjson::Value& _json = readdoc["json"];
    const char* ch = _json.GetString();
    log("ch  =%s",ch);

    char levelChar[20];
    TargetPlatform target=Application::getInstance()->getTargetPlatform();
    if (target==kTargetIpad) {
        sprintf(levelChar, "Ipad%d",level);
    }else{
        sprintf(levelChar, "hiddenPicture%d",level);
    }

    
    rapidjson::Value& _array = readdoc[levelChar];
    
    log("json  =%d",_array.Capacity());
    if(_array.IsArray())
    {
        CCLOG("关卡信息");
        for(int i=0; i<_array.Capacity(); i++)
        {
            ValueMap vm;
            //CCLOG("%d", i);
            rapidjson::Value& arraydoc = _array[i];
            const char* name;
            int _inttag;
            int x;
            int y;
            int rotation;
            if(arraydoc.HasMember("inttag"))
            {
                _inttag = arraydoc["inttag"].GetInt();
                CCLOG("%d", _inttag);
                std::string  k("inttag");
                cocos2d::Value v(_inttag);
                vm[k]=v;
            }
            if(arraydoc.HasMember("picName"))
            {
                name = arraydoc["picName"].GetString();
                CCLOG("%s", name);
                std::string  k("picName");
                cocos2d::Value v(name);
                vm[k]=v;
            }
            if(arraydoc.HasMember("positionX"))
            {
                x = arraydoc["positionX"].GetInt();
                CCLOG("%d", x);
                std::string  k("positionX");
                cocos2d::Value v(x);
                vm[k]=v;
            }
            if(arraydoc.HasMember("positionY"))
            {
                y = arraydoc["positionY"].GetInt();
                CCLOG("%d", y);
                std::string  k("positionY");
                cocos2d::Value v(y);
                vm[k]=v;
            }
            if(arraydoc.HasMember("rotation"))
            {
                rotation = arraydoc["rotation"].GetInt();
                CCLOG("%d", rotation);
                std::string  k("rotation");
                cocos2d::Value v(rotation);
                vm[k]=v;
            }
            vv.push_back(cocos2d::Value(vm));
        }
    }
    
    vvAll=vv;
    return (cocos2d::Value)vv;

}

cocos2d::Value LevelData::paeseLevelSmallPicture(int level)
{
    ValueVector vvAll;
    ValueVector vv;
    std::string load_str;
    load_str = cocos2d::FileUtils::getInstance()->getStringFromFile("myhero.json");
    rapidjson::Document readdoc;
    readdoc.Parse<0>(load_str.c_str());
    if(readdoc.HasParseError())
    {
        CCLOG("GetParseError%s\n", readdoc.GetParseError());
    }
    
    rapidjson::Value& _json = readdoc["json"];
    const char* ch = _json.GetString();
    log("ch  =%s",ch);
    
    char levelChar[20];
    sprintf(levelChar, "showPicture%d",level);
    rapidjson::Value& _array = readdoc[levelChar];
    
    log("json  =%d",_array.Capacity());
    if(_array.IsArray())
    {
        CCLOG("关卡小图信息");
        for(int i=0; i<_array.Capacity(); i++)
        {
            ValueMap vm;
            rapidjson::Value& arraydoc = _array[i];
            const char* name;
            int _intID;
            bool iscover;
            if(arraydoc.HasMember("id"))
            {
                _intID = arraydoc["id"].GetInt();
                std::string  k("id");
                cocos2d::Value v(_intID);
                vm[k]=v;
            }
            if(arraydoc.HasMember("pictureName"))
            {
                name = arraydoc["pictureName"].GetString();
                CCLOG("%s", name);
                std::string  k("pictureName");
                cocos2d::Value v(name);
                vm[k]=v;
            }
            if(arraydoc.HasMember("isCover"))
            {
                iscover = arraydoc["isCover"].GetBool();
                CCLOG("%d", iscover);
                std::string  k("isCover");
                cocos2d::Value v(iscover);
                vm[k]=v;
            }
            vv.push_back(cocos2d::Value(vm));
        }
    }
    
    vvAll=vv;
    return (cocos2d::Value)vv;

}


cocos2d::Value LevelData::paeseLevelShape(int randNum)
{
    ValueVector vvAll;
    ValueVector vv;
    std::string load_str;
    load_str = cocos2d::FileUtils::getInstance()->getStringFromFile("myhero.json");
    rapidjson::Document readdoc;
    readdoc.Parse<0>(load_str.c_str());
    if(readdoc.HasParseError())
    {
        CCLOG("GetParseError%s\n", readdoc.GetParseError());
    }
    
    rapidjson::Value& _json = readdoc["json"];
    const char* ch = _json.GetString();
    log("ch  =%s",ch);
    
    char randNumChar[10];
    sprintf(randNumChar, "shape%d",randNum);
    rapidjson::Value& _array = readdoc[randNumChar];
    
    log("json  =%d",_array.Capacity());
    if(_array.IsArray())
    {
        CCLOG("关卡形状信息");
        for(int i=0; i<_array.Capacity(); i++)
        {
            ValueMap vm;
            rapidjson::Value& arraydoc = _array[i];
            
            if(arraydoc.HasMember("s1"))
            {
                int _intS1 = arraydoc["s1"].GetInt();
                std::string  k("s1");
                cocos2d::Value v(_intS1);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s2"))
            {
                int _intS2 = arraydoc["s2"].GetInt();
                std::string  k("s2");
                cocos2d::Value v(_intS2);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s3"))
            {
                int _intS3 = arraydoc["s3"].GetInt();
                std::string  k("s3");
                cocos2d::Value v(_intS3);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s4"))
            {
                int _intS4 = arraydoc["s4"].GetInt();
                std::string  k("s4");
                cocos2d::Value v(_intS4);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s5"))
            {
                int _intS5 = arraydoc["s5"].GetInt();
                std::string  k("s5");
                cocos2d::Value v(_intS5);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s6"))
            {
                int _intS6 = arraydoc["s6"].GetInt();
                std::string  k("s6");
                cocos2d::Value v(_intS6);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s7"))
            {
                int _intS7 = arraydoc["s7"].GetInt();
                std::string  k("s7");
                cocos2d::Value v(_intS7);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s8"))
            {
                int _intS8 = arraydoc["s8"].GetInt();
                std::string  k("s8");
                cocos2d::Value v(_intS8);
                vm[k]=v;
            }
            if(arraydoc.HasMember("s9"))
            {
                int _intS9 = arraydoc["s9"].GetInt();
                std::string  k("s9");
                cocos2d::Value v(_intS9);
                vm[k]=v;
            }
            vv.push_back(cocos2d::Value(vm));
        }
    }
    
    vvAll=vv;
    return (cocos2d::Value)vv;
    
}