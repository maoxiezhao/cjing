#include"luaContext.h"
#include"game\app.h"

const string LuaContext::module_main_name = "Main";

void LuaContext::RegisterMainModule()
{
	static const luaL_Reg functions[] = {
		{"sayHello",main_api_hello},
		{"Exit",main_api_exit},
		{nullptr,nullptr }
	};

	RegisterFunction(module_main_name, functions);

	lua_getglobal(l, module_name.c_str());
							// cjing
	lua_getfield(l, -1, "Main");
	lua_setfield(l, LUA_REGISTRYINDEX, module_main_name.c_str());
							// cjing
	lua_pop(l, 1);
}

/**
*	\brief ִ��lua�ű�main:on_start
*/
void LuaContext::OnMainStart()
{
	PushMain(l);
	OnStart();
	lua_pop(l, 1);
}

void LuaContext::OnMainUpdate()
{
	PushMain(l);
	OnUpdate();
	lua_pop(l, 1);
}

void LuaContext::OnMainFinish()
{
	PushMain(l);
	OnFinish();
	lua_pop(l, 1);
}

/**
*	\brief ������
*
*	�����¼���Ҫ���ݸ���ǰ��menu
*	\return ���ص�ǰ�Ƿ�����Ч����
*/
bool LuaContext::OnMainInput(const InputEvent& event)
{
	PushMain(l);
	bool handle = OnInput(event);
	if (!handle)
		handle = OnMenuInput(-1, event);
	lua_pop(l, 1);
	return handle;
}

int LuaContext::main_api_hello(lua_State* l)
{
	return LuaTools::ExceptionBoundary(l, [&] {
		
		cout << "hello world." << endl;
		return 0;
	});
}

int LuaContext::main_api_exit(lua_State*l)
{
	return LuaTools::ExceptionBoundary(l, [&] {
		
		GetLuaContext(l).GetApp()->SetExiting(true);
		return 0;
	});
}

void LuaContext::PushMain(lua_State*l)
{
	lua_getfield(l, LUA_REGISTRYINDEX, module_main_name.c_str());
}