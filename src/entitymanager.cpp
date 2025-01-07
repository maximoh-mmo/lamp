#include "stdafx.h"
#include "entitymanager.h"
#include <stdexcept>
#include "ecs.h"

// Initialize queue with all entity IDs
EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		m_availableEntities.push(entity);
	}
}

// Pop the next available entity ID and increase living count
Entity EntityManager::CreateEntity()
{
	if (m_livingEntityCount >= MAX_ENTITIES)
		throw std::runtime_error("Too many entities in existence.");

	Entity id = m_availableEntities.front();
	m_availableEntities.pop();
	++m_livingEntityCount;

	return id;
}

// Destroy entity and recycle ID, decrease living count
void EntityManager::DestroyEntity(Entity entity)
{
	if (entity >= MAX_ENTITIES)
		throw std::runtime_error("Entity out of range.");

	// reset clears the signature
	m_signatures[entity].reset();
	m_availableEntities.push(entity);
	--m_livingEntityCount;
}

// Add entity signature into array (index corresponds to entity ID)
void EntityManager::SetSignature(Entity entity, Signature signature)
{
	if (entity >= MAX_ENTITIES)
		throw std::runtime_error("Entity out of range.");

	m_signatures[entity] = signature;
}

// Return signature of entity from array (index corresponds to entity ID)
Signature EntityManager::GetSignature(Entity entity) const
{
	if (entity >= MAX_ENTITIES)
		throw std::runtime_error("Entity out of range.");

	return m_signatures[entity];
}