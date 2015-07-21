
#include "XmlParser.h" 

USING_NS_CC;

XmlParser * XmlParser::createWithFile(const char *fileName) 
{ 
	XmlParser *pRet = new XmlParser(); 
	if(pRet->initWithFile(fileName)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	CC_SAFE_DELETE(pRet); 
	return nullptr; 
} 

bool XmlParser::initWithFile(const char* fileName) 
{
	auto sharedFileUtils = FileUtils::getInstance();
	std::string path = sharedFileUtils->fullPathForFilename(fileName);

	Data data = sharedFileUtils->getDataFromFile(path);
	//Data构建string
	content = std::string((const char*)data.getBytes(),0,data.getSize());
	log("content : %s",content.c_str()); 

	//开始解析
	this->parse();

	return true; 
} 

void XmlParser::parse()
{
	tinyxml2::XMLDocument xmlDoc;

	xmlDoc.Parse(content.c_str());

	tinyxml2::XMLElement *root = xmlDoc.RootElement();

	tinyxml2::XMLElement *note =root->FirstChildElement("Note");  

	while(note){

		row = ValueMap();

		//取id属性
		const tinyxml2::XMLAttribute *att =  note->FirstAttribute();
		std::pair<std::string,Value> idPair("id",Value(att->Value()));
		row.insert(idPair);

		//取CDate元素内容
		tinyxml2::XMLElement *dateElement =note->FirstChildElement("CDate"); 
		row["CDate"] = Value(dateElement->GetText());
		
		//取Content元素内容
		tinyxml2::XMLElement *contentElement =note->FirstChildElement("Content");
		row["Content"] = Value(contentElement->GetText());

		//取UserID元素内容
		tinyxml2::XMLElement *userIDElement =note->FirstChildElement("UserID");
		row["UserID"] = Value(userIDElement->GetText());

		list.push_back(Value(row));

		if(note->NextSibling() == nullptr){
			break;
		}else {
			note = note->NextSibling()->ToElement();
		}

	}

}
