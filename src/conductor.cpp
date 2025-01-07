#include "stdafx.h"
#include "conductor.h"

void Conductor::Init()
{
	m_componentManager = std::make_unique<ComponentManager>();
	m_entityManager = std::make_unique<EntityManager>();
	m_systemManager = std::make_unique<SystemManager>();
}

void Conductor::DestroyEntity(Entity entity)
{
	m_entityManager->DestroyEntity(entity);
	m_componentManager->EntityDestroyed(entity);
	m_systemManager->EntityDestroyed(entity);
}

Entity Conductor::CreateEntity() const
{
	return m_entityManager->CreateEntity();
}
