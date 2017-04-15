#ifndef _FILE_DATA_H_
#define _FILE_DATA_H_

#include"common\common.h"

/**
*	\brief ��ԴĿ¼����
*	
*	ʹ��physfs����ָ������ԴĿ¼
*/
namespace FileData
{
	bool OpenData(const string&dataName, const string& dataPath);
	void CloseData();
	bool IsOpen();

	bool IsFileExists(const string& name);
	string ReadFile(const string& name);
	void SaveFile(const string& name,const string&buffer);
	bool DeleteFile(const string& name);
}

#endif