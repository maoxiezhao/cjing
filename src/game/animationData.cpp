#include "animationData.h"
#include "core\debug.h"

AnimationData::AnimationData()
{
}

AnimationData::AnimationData(const string & imageName, const std::deque<AnimationDirectionData>& directions, uint32_t frameDelay, int frameLoop)
{
}

string AnimationData::GetImageName() const
{
	return mImageName;
}

uint32_t AnimationData::GetFrameDelay() const
{
	return mFrameDelay;
}

int AnimationData::GetFrameLoop() const
{
	return mFrameLoop;
}

std::deque<AnimationDirectionData>& AnimationData::GetDirections()
{
	return mDirections;
}

AnimationLuaData::AnimationLuaData()
{
}

/**
*	\brief 从Lua文件中导入数据
*
*	将当前AnimationLuaData保存在LUA_REGISTRE,同时根据格式将
*	animation注册上解析函数，在解析函数存储数据
*/
bool AnimationLuaData::ImportFromLua(lua_State * l)
{
	lua_pushlightuserdata(l, this);	// lightuserdata
	lua_setfield(l, LUA_REGISTRYINDEX, "Animation");
	lua_register(l, "animation", LuaAnimation);
	if (lua_pcall(l,0,0,0) != 0)
	{
		Debug::Error("Failed to load animation datafile.");
		lua_pop(l,1);	// ?????
		return false;
	}
	return true;
}

/**
*	\brief animation 格式解析
*/
int AnimationLuaData::LuaAnimation(lua_State * l)
{
	return 0;
}

const std::map<string, AnimationData>& AnimationLuaData::GetAnimations() const
{
	return mAnimations;
}

string AnimationLuaData::GetDefaultName() const
{
	return mDefaultName;
}

