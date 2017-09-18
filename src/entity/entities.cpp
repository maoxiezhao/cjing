#include "entities.h"
#include "core\video.h"
#include "lua\luaContext.h"

Entities::Entities(Game&game, Map&map):
	mGame(game),
	mMap(map),
	mEntityNamed(),
	mAllEntities(),
	mEntityToDraw(),
	mEntityToRemove(),
	mCamera(nullptr)
{
	// 初始化每层的layer

	// 初始化四叉树

	// 添加相机,Test:临时设置为屏幕中点，视野为整个屏幕
	mCamera = std::make_shared<Camera>();
	mCamera->SetSize(Video::GetScreenSize() / 2);
	mCamera->SetPos({ Video::GetScreenSize().width / 2, Video::GetScreenSize().height / 2 });
	AddEntity(mCamera);
}

Entities::~Entities()
{
	mEntityNamed.clear();
	mEntityToDraw.clear();
	mEntityToRemove.clear();
	mAllEntities.clear();
}

/**
*	\brief 更新entity
*/
void Entities::Update()
{
	for (const auto& entity : mAllEntities)
	{
		entity->Update();
	}
	mEntityToDraw.clear();
}

/**
*	\brief 绘制entity
*/
void Entities::Draw()
{
	// 添加需要绘制的entity，这里是只要entity在
	// 在相机范围时才添加到绘制列表
	if (mEntityToDraw.empty())
	{
		for (const auto& entity : mAllEntities)
		{
			Rect aroundCamera(
				mCamera->GetPos().x - mCamera->GetSize().width,
				mCamera->GetPos().y - mCamera->GetSize().height,
				mCamera->GetSize().width * 2,
				mCamera->GetSize().height * 2);

			if (entity->GetRectBounding().Overlaps(aroundCamera))
			{
				int layer = entity->GetLayer();
				mEntityToDraw[layer].push_back(entity);
			}
		}
	}

	// 根据层级绘制entity
	for (int layer = mMap.GetMinLayer(); layer <= mMap.GetMaxLayer(); layer++)
	{
		// 绘制tile

		// 绘制普通entity
		auto curLayerEntityToDraw = mEntityToDraw[layer];
		for (const auto& entity : curLayerEntityToDraw)
		{
			entity->Draw();
		}
	}
}

void Entities::SetSuspended(bool suspended)
{
}

/**
*	\brief 返回相机
*/
CameraPtr Entities::GetCamear() const
{
	return mCamera;
}

/**
*	\brief 返回entities的集合
*/
EntityList Entities::GetEntities()
{
	return mAllEntities;
}

/**
*	\brief 根据entityData创建entities
*/
void Entities::InitEntities(const MapData& mapData)
{
	// 按照层级顺序创建entity
	for (int curLayer = mapData.GetMinLayer(); curLayer <= mapData.GetMaxLayer(); curLayer++)
	{
		for (int index = 0; index < mapData.GetEntityCountByLayer(curLayer); index++)
		{
			const EntityData& entityData = mapData.GetEntity(curLayer, index);
			if (!GetLuaContext().CreateEntity(entityData, mMap))
			{
				Debug::Error("Failed to create entity.");
			}
		}
	}
}

/**
*	\biref 添加一个新的entity
*/
void Entities::AddEntity(const EntityPtr& entity)
{
	if (entity == nullptr)
	{
		return;
	}
	Debug::CheckAssertion(mMap.IsValidLayer(entity->GetLayer()),
		"Invalid entity layer in adding entity.");

	mAllEntities.push_back(entity);
	entity->SetMap(&mMap);
}

void Entities::RemoveEntity(Entity& entity)
{
}

LuaContext & Entities::GetLuaContext()
{
	return mGame.GetLuaContext();
}

Map & Entities::GetMap()
{
	return mMap;
}

