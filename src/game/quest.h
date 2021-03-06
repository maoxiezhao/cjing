#pragma once

/**
*	\brief 任务模块
*
*	任务模块提供处理任务的基本接口，同时负责从lua Data
*	中读取相应的任务数据，并负责维护整个任务链，负责推进
*	任务目标
*/
namespace Quest
{
class QuestManager
{
public:
	~QuestManager() {}

	QuestManager& GetInstance() {}

private:
	QuestManager() {}
};

}