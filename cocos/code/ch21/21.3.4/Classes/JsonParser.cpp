
#include "JsonParser.h" 

ValueMap JsonParser::decode(string content)
{
	rapidjson::Document document;
	document.Parse<0>(content.c_str());

	//解析错误
	CCASSERT(!document.HasParseError(), "Parsing to document failure.");

	CCLOG("Parsing to document succeeded.");

	CC_ASSERT(document.IsObject() && document.HasMember("ResultCode"));
	const rapidjson::Value &val_ResultCode= document["ResultCode"]; //读取ResultCode 
	//判断ResultCode类型 
	CC_ASSERT(val_ResultCode.IsInt());
	int resultCode = val_ResultCode.GetInt(); 

	ValueMap dict;
	dict["ResultCode"] = Value(resultCode);

	//判断是否有Record
	if (document.IsObject() && document.HasMember("Record")) {
		const rapidjson::Value &records= document["Record"]; //读取中文的数组 
		//判断是不是数组 
		CC_ASSERT(records.IsArray());

		ValueVector listData;

		for(unsigned int i = 0; i < records.Size();i++) //如果不是数组，这一行会报错 
		{ 
			ValueMap row;

			//获得一条记录对象
			const rapidjson::Value &record = records[i]; 

			//判断这个record有没有ID键 
			CC_ASSERT(record.HasMember("ID"));
			const rapidjson::Value &val_id = record["ID"]; 
			//判断ID类型 
			CC_ASSERT(val_id.IsInt());
			int id = val_id.GetInt(); 
			row["ID"] = Value(id);

			//判断这个record有没有CDate键 
			CC_ASSERT(record.HasMember("CDate"));
			const rapidjson::Value &val_CDate = record["CDate"]; 
			//判断CDate类型 
			CC_ASSERT(val_CDate.IsString());
			const char* cDate = val_CDate.GetString(); 
			row["CDate"] = Value(cDate);

			//判断这个record有没有Content键 
			CC_ASSERT(record.HasMember("Content"));
			const rapidjson::Value &val_Content = record["Content"]; 
			//判断Content类型 
			CC_ASSERT(val_Content.IsString());
			const char* cContent = val_Content.GetString(); 
			row["Content"] = Value(cContent);

			listData.push_back(Value(row));
		}
		
		dict["Record"] = Value(listData);
		
	}
	return dict;
}
