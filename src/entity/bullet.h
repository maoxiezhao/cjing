#pragma once

#include "entity\entity.h"

/**
*	\brief �ӵ�ʵ����
*/
class Bullet : public Entity
{
public:
	enum class BULLET_TYPE
	{
		BULLET_PLAYER = 0,
		BULLET_ENEMY,
		BULLET_CUSTOM,
	};

	Bullet(const std::string& templName, int layer);
	static EntityPtr Create(const std::string& templName, int layer);

	/** system */
	virtual void Update();
	void Stop();
	void ComputeDemage(Entity& entity);

	virtual EntityType GetEntityType()const;
	virtual const string GetLuaObjectName()const;

	/** notify */
	virtual void NotifyBeforeCreated();
	virtual void NotifyAfterCreated();
	virtual void NotifyCollisionWithEnemy(Enemy& enemy);
	virtual void NotifyCollisionWithPlayer(Player& player);
	virtual void NotifyObstacleReached();

	/** status */
	virtual bool IsObstacle(Entity& entity)const;
	virtual bool IsObstacleEnemy()const;
	virtual bool IsObstaclePlayer()const;
	virtual void SetFacingDegree(float degree);
	virtual float GetFacingDegree()const;

	void SetDisapearAnimTime(uint32_t time);
	uint32_t GetDisapearAnimTime()const;
	void SetAliveTime(uint32_t time);
	uint32_t GetAliveTime()const;

	void SetBulletType(BULLET_TYPE type);
	int GetBulletType()const;
	bool IsStop();
	bool IsFiring()const;

	/** extra status */
	void SetDemage(int demage);
	int GetDemage()const;

private:
	BULLET_TYPE mBulletType;
	uint32_t mDisappearDate;
	uint32_t mDisappearAnimTime;

	bool mIsStopping;	/** �Ƿ���ֹͣ�ģ����ӵ��Ѿ�ֹͣ���� */
	bool mStopNow;		/** �Ƿ�����ֹͣ */
	int mDemage;		/** �ӵ��˺� */
};