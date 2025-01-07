#pragma once
#include <array>
#include <bitset>
#include <queue>

#include "ecs.h"

/// <summary>
/// 
/// EntityManager class manages all entities in the game.
/// Responsible for creating and destroying entities,
/// alongside maintaining a list of available entity ids.
/// 
/// </summary>
class EntityManager
{
public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity) const;

private:
	std::queue<Entity> m_availableEntities{};
	std::array<Signature, MAX_ENTITIES> m_signatures{};
	uint32_t m_livingEntityCount{};
};