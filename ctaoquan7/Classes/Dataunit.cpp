//
//  Dataunit.cpp
//  ctaoquan7
//
//  Created by lizhengyan on 15/7/7.
//
//

#include "Dataunit.h"
USING_NS_CC;

bool Dataunit::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    auto sharedFileUtils =FileUtils::getInstance();
    std::string fullFilename=sharedFileUtils->fullPathForFilename("test.txt");  //获取路径的
    log("fullpath path=%s",fullFilename.c_str());
    
    
    
    Data data =sharedFileUtils->getDataFromFile(fullFilename);
    

    std::string content2 = sharedFileUtils->getStringFromFile(fullFilename);
    log("content2=%s",content2.c_str());  //读取文件内容
    
    
    std::string writeablePath = sharedFileUtils->getWritablePath();
    std::string fileName = writeablePath+"test1.txt";
    log("WritefilePath=%s",fileName.c_str());
    
    char txtCont[100]="wo men dou shi zhong guo  ren \n";
    FILE * fp=fopen(fileName.c_str(), "wb") ;
    if (fp)
    {
        size_t ret=fwrite(txtCont, 1, strlen(txtCont), fp);
        if(ret !=0){
            log("Write file success!");
            
        }
        fclose(fp);
    }
    

    
    
    return true;
}


