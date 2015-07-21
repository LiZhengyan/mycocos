#include "NoteDAO.h"

string NoteDAO::dbDirectoryFile()
{
	auto sharedFileUtils = FileUtils::getInstance();
	string writablePath = sharedFileUtils->getWritablePath();
	string fullPath = writablePath + "NotesList.sqlite3";

	return fullPath;
}

//��ʼ�����ݿ�
int NoteDAO::initDB()
{
	auto sharedFileUtils = FileUtils::getInstance();

	string path = dbDirectoryFile();

	bool isExist = false;
	isExist = sharedFileUtils->isFileExist(path);
	if (!isExist) {
		log("NotesList.sqlite3 doesn't exist.");
		return -1;
	}

	sqlite3* db= NULL;
	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		char *err;
		string createSQL = "CREATE TABLE IF NOT EXISTS Note (cdate TEXT PRIMARY KEY, content TEXT)";
		if (sqlite3_exec(db,createSQL.c_str(),NULL,NULL,&err) != SQLITE_OK) {
			sqlite3_close(db);
			CCASSERT(false, "Create table failure.");
		}
		sqlite3_close(db);
	}

	return 0;
}

//����Note����
int NoteDAO::create(string pDate, string pContent)
{
	//��ʼ�����ݿ�
	initDB();

	sqlite3* db= NULL;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		string sqlStr = "INSERT OR REPLACE INTO note (cdate, content) VALUES (?,?)";
		sqlite3_stmt *statement;
		//Ԥ�������
		if (sqlite3_prepare_v2(db, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//�󶨲�����ʼ
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			//�ַ�ת����ʹcocos2d-x��win32��wp8ƽ̨֧��������ʾ
			pContent = MyUtility::gbk_2_utf8(pContent);
#endif
			sqlite3_bind_text(statement, 2, pContent.c_str(), -1, NULL);

			//ִ�в���
			if (sqlite3_step(statement) != SQLITE_DONE) {
				CCASSERT(false, "Insert Data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//ɾ��Note����
int NoteDAO::remove(string pDate)
{
	//��ʼ�����ݿ�
	initDB();

	sqlite3* db= NULL;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		string sqlStr = "DELETE  from note where cdate =?";
		sqlite3_stmt *statement;
		//Ԥ�������
		if (sqlite3_prepare_v2(db, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//�󶨲�����ʼ
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);
			//ִ��ɾ��
			if (sqlite3_step(statement) != SQLITE_DONE) {
				CCASSERT(false, "Delete Data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//�޸�Note����
int NoteDAO::modify(string pDate, string pContent)
{
	//��ʼ�����ݿ�
	initDB();

	sqlite3* db= NULL;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		string sqlStr = "UPDATE note set content=? where cdate =?";
		sqlite3_stmt *statement;
		//Ԥ�������
		if (sqlite3_prepare_v2(db, sqlStr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//�󶨲�����ʼ
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			//�ַ�ת����ʹcocos2d-x��win32��wp8ƽ̨֧��������ʾ
			pContent = MyUtility::gbk_2_utf8(pContent);
#endif
			sqlite3_bind_text(statement, 1, pContent.c_str(), -1, NULL);			
			sqlite3_bind_text(statement, 2, pDate.c_str(), -1, NULL);

			//ִ���޸�����
			if (sqlite3_step(statement) != SQLITE_DONE) {
				CCASSERT(false, "Upate Data failure.");
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return 0;
}

//��ѯ�������ݷ���
ValueVector NoteDAO::findAll()
{
	//��ʼ�����ݿ�
	initDB();
	sqlite3* db= NULL;

	string path = dbDirectoryFile();
	ValueVector listData;

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		string qsql = "SELECT cdate,content FROM Note";
		sqlite3_stmt *statement;
		//Ԥ�������
		if (sqlite3_prepare_v2(db, qsql.c_str(), -1, &statement, NULL) == SQLITE_OK) {
			//ִ��
			while (sqlite3_step(statement) == SQLITE_ROW) {

				char *cdate = (char *)sqlite3_column_text(statement, 0);
				char *content = (char *)sqlite3_column_text(statement, 1);

				ValueMap dict ;
				dict["date"] = Value(cdate);
				dict["content"] = Value(content);

				listData.push_back(Value(dict));
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return listData;
}


//����������ѯ���ݷ���
ValueMap NoteDAO::findById(string pDate)
{
	//��ʼ�����ݿ�
	initDB();
	sqlite3* db= NULL;
	ValueMap dict ;

	string path = dbDirectoryFile();

	if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
		sqlite3_close(db);
		CCASSERT(false, "DB open failure.");
	} else {
		string qsql = "SELECT cdate,content FROM Note where cdate =?";
		sqlite3_stmt *statement;
		//Ԥ�������
		if (sqlite3_prepare_v2(db, qsql.c_str(), -1, &statement, NULL) == SQLITE_OK) {

			//�󶨲�����ʼ
			sqlite3_bind_text(statement, 1, pDate.c_str(), -1, NULL);

			//ִ��
			if (sqlite3_step(statement) == SQLITE_ROW) {

				char *cdate = (char *)sqlite3_column_text(statement, 0);
				char *content = (char *)sqlite3_column_text(statement, 1);

				dict["date"] = Value(cdate);
				dict["content"] = Value(content);
			}
		}
		sqlite3_finalize(statement);
		sqlite3_close(db);
	}
	return dict;
}
