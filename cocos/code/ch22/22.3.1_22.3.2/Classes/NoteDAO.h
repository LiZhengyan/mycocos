//
//  Created by �ض��� on 2014-5-18.
//  ������վ��http://www.cocoagame.net
//  �ǽ�iOS�������߿��ã�http://v.51work6.com
//  �ǽ�iOS��������΢����http://weibo.com/u/3215753973
//  ����΢����http://weibo.com/516inc
//  QQ��1575716557 ���䣺jylong06@163.com
//  QQ����Ⱥ��389037167/327403678
//


#ifndef  _MY_NOTEDAO_H_
#define  _MY_NOTEDAO_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include <sqlite3.h>
#else
#include "sqlite3.h"
#endif

#include "MyUtility.h"

using namespace std;
USING_NS_CC;

class NoteDAO 
{
	sqlite3 *db;
public:

	//������ݿ��ļ�·��
	static string dbDirectoryFile();

	//��ʼ�����ݿ�
	static int initDB();

	//����Note����
	static int create(string pDate, string pContent);

	//ɾ��Note����
	static int remove(string pDate);

	//�޸�Note����
	static int modify(string pDate, string pContent);

	//��ѯ�������ݷ���
	static ValueVector findAll();

	//����������ѯ���ݷ���
	static ValueMap findById(string pDate);

};

#endif // _MY_NOTEDAO_H_
