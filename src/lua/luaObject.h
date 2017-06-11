#ifndef _LUA_OBJECT_H_
#define _LUA_OBJECT_H_

#include"common\common.h"
#include"lua\luaTools.h"

class LuaContext;

/**
*	\brief luaObject �ṩ��C++������lua userdata�ķ�ʽ����
*/
class LuaObject : public std::enable_shared_from_this<LuaObject>
{
public:
	LuaObject();
	virtual ~LuaObject();

	LuaContext* GetLuaContext()const;
	void SetLuaContext(LuaContext* luaContext);

	bool IsKnowToLua()const;
	void SetKnowToLua(bool knowToLua);

	virtual const string GetLuaObjectName()const = 0;

private:
	LuaContext* mLuaContext;

	bool mKnowToLua;	// �Ƿ��Ѿ����뵽lua

};

using LuaObjectPtr = std::shared_ptr<LuaObject>;


#endif