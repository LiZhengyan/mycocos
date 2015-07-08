

#include "json/stringbuffer.h"
#include "json/document.h"
#include "json/writer.h"


//    {
//        "resources": {
//            "string": [
//                       {
//                       "name": "app_name",
//                       "text": "小黄人大作战"
//                       },
//                       {
//                       "name": "exit_dialog_title",
//                       "text": "提醒"
//                       },
//                       {
//                       "name": "exit_dialog_text",
//                       "text": "你确定退出吗？"
//                       },
//                       {
//                       "name": "exit_dialog_btn_yes",
//                       "text": "确定"
//                       },
//                       {
//                       "name": "exit_dialog_text_no",
//                       "text": "返回"
//                       }
//                       ]	
//        }
//    }
//    

	
		
		//*** 读取 json 文件 ***
	rapidjson::Document readdoc;

	ssize_t size = 0;
	std::string load_str;
		
		// getFileData 如果不指定，读取根目录是 Resource 文件夹
	unsigned char* titlech = FileUtils::getInstance()->getFileData("strings.json", "r", &size);
	load_str = std::string((const char*)titlech,size);
	readdoc.Parse<0>(load_str.c_str());
	
	rapidjson::Value& _resources = readdoc["resources"];
	rapidjson::Value& _string = _resources["string"];
	if(!_string.IsArray())
			return false;
	
	for (rapidjson::SizeType i=0 ; i<_string.Size(); i++) {
		const   rapidjson::Value &p =_string[i];
		if(p.HasMember("name"))
		{
			log("%s",p["name"].GetString());
			//int tapOp = tapOpposite.GetInt();
			//float inter = interval.GetDouble();
			//int ball = ballNum.GetInt();
			log("%s",p["text"].GetString());
		}
	}
	
	
	
	
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	
	// json object 格式添加 “名称/值” 对
	for (int i=0; i<3; i++) {
		rapidjson::Value object(rapidjson::kObjectType);

		object.AddMember("name", "tom", allocator);
		object.AddMember("text", "test", allocator);
	
		// json 加入数组
		array.PushBack(object, allocator);
	}
//    writedoc.AddMember("json", "json string", allocator);
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("string", array, allocator);
	
	writedoc.AddMember("resources", object, allocator);
	
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);
	
	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("myhero.json");
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s",buffer.GetString());
	
