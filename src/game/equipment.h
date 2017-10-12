#pragma once

#include"common\common.h"

class Savegame;

/**
*	\brief equipment 类包含有当前的游戏数值属性
*	同时管理当前所拥有的item
*
*	equipment是player的数值显示管理,所有的数值通
*	过该类管理在savegame中，同时保存有两份数据
*	（该类和savegame)
*/
class Equipment
{
public:
	Equipment(Savegame& savegame);

	/**** ***** Setter/Getter **** *****/
	int GetLife()const;
	void SetLife(int life);

private:
	Savegame& mSavegame;
};