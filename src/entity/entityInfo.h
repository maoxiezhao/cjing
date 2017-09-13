#pragma once

#include"game\enumInfo.h"

/**
*	\brief Entity 类型数据相关描述
*/
enum EntityType
{
	TITLE,			/** 地图块 */
	DYNAMIC_TITLE,  /** 动态地图块 */
	DESTIMATION,	/** 目标点 */
	UNKNOW,			/** 未知的类型 */
};

// 用于获取key枚举值对应的字符
template<>
struct EnumInfoTraits<EntityType>
{
	static const string prettyName;
	static const EnumInfo<EntityType>::nameType names;
};
