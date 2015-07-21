
#include "JsonParser.h" 

USING_NS_CC;

JsonParser * JsonParser::createWithArray(ValueVector pListData) 
{ 
	JsonParser *pRet = new JsonParser(); 
	if(pRet->initWithArray(pListData)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	CC_SAFE_DELETE(pRet); 
	return NULL; 
} 

bool JsonParser::initWithArray(ValueVector pListData)
{ 
	this->listData = pListData;
	return true; 
}

void JsonParser::encode()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value array(rapidjson::kArrayType);
	
	for (auto& v: listData)
	{
		ValueMap row = v.asValueMap();

		rapidjson::Value object(rapidjson::kObjectType);

		rapidjson::Value v_id;
		v_id.SetString(row["ID"].asString().c_str(), allocator);
		object.AddMember("ID", v_id, allocator);

		rapidjson::Value v_Date;
		v_Date.SetString(row["CDate"].asString().c_str(), allocator);
		object.AddMember("CDate", v_Date, allocator);
		
		rapidjson::Value v_Content;
		v_Content.SetString(row["Content"].asString().c_str(), allocator);
		object.AddMember("Content", v_Content, allocator);

		rapidjson::Value v_UserID;
		v_UserID.SetString(row["UserID"].asString().c_str(), allocator);
		object.AddMember("UserID", v_UserID, allocator);

		array.PushBack(object, allocator);
	}

	document.AddMember("ResultCode", 0, allocator);
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

	document.Accept(writer);

	auto out = buffer.GetString();

	log("out: %s", out);

}
