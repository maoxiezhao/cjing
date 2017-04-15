#include"luaTools.h"
#include"luaException.h"
#include"core\debug.h"
#include<iostream>
#include<sstream>

namespace LuaTools
{
	LuaRef CreateRef(lua_State * l)
	{
		return LuaRef(l, luaL_ref(l, LUA_REGISTRYINDEX));
	}
	LuaRef CreateRef(lua_State * l, int index)
	{
		lua_pushvalue(l, index);
		return LuaRef(l,luaL_ref(l,LUA_REGISTRYINDEX));
	}

	bool CallFunction(lua_State*l, int arguments, int results, const string& functionName)
	{
		if (lua_pcall(l, arguments, results, 0) != 0)
		{
			Debug::Error(std::string("In ") + functionName + ": " + lua_tostring(l, -1));
			lua_pop(l, 1);
			return false;
		}
		return true;;
	}

	int GetPositiveIndex(lua_State * l, int index)
	{
		int positiveIndex = index;
		if (index < 0 && index >= -lua_gettop(l))
			positiveIndex = lua_gettop(l) + index + 1;
		
		return positiveIndex;
	}

	void CheckType(lua_State * l, int index, int exceptedType)
	{
		if (lua_type(l, index) != exceptedType)
			ArgError(l, index, string("excepted") + string(luaL_typename(l, exceptedType)) +
				" but get" + luaL_typename(l, index));
	}

	int CheckInt(lua_State * l, int index)
	{
		if (!lua_isnumber(l, index))
			ArgError(l, index, string("Excepted:integer,got ") + luaL_typename(l, index));

		return (int)lua_tointeger(l,index);
	}

	string CheckString(lua_State * l, int index)
	{
		if (!lua_isstring(l, index))
			ArgError(l, index, string("Excepted:string,got ") + luaL_typename(l, index));
		return lua_tostring(l, index);
	}

	LuaRef CheckFunction(lua_State * l, int index)
	{
		CheckType(l, index, LUA_TFUNCTION);
		return CreateRef(l, index);;
	}

	/**
	*	\brief ����Lua_error�׳�luaException�쳣.
	*/
	void Error(lua_State * l, const string & message)
	{
		throw LuaException(l, message);
	}

	/**
	*	\brief �׳�luaException���õĵ� index ������������
	*
	*	�ú���������.
	*/
	void ArgError(lua_State * l, int index, const string & message)
	{
		std::ostringstream oss;
		lua_Debug info;
		if (!lua_getstack(l, 0, &info))		// ��ȡ��ǰ���к����Ļ��¼
		{
			// ??????
			oss << "Bad argument #" << index << "(" << message << ")";
			Error(l, oss.str());
		}
			
		lua_getinfo(l, "n", &info);			// ���name�򣬼���ǰ������������
		if (string(info.namewhat) == "method")
		{
			// ?????
			oss << "Calling:" << info.name << " failed. (" << message << ")";
			Error(l, oss.str());
		}

		if (info.name == nullptr)
			info.name = "?";

		oss << "Bad argument #" << index << " to " <<  info.name << "(" << message << ")";
		Error(l,oss.str());
	}




}