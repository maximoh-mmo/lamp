#include "stdafx.h"
#include "systemmanager.h"

#include "system.h"


// Erase a destroyed entity from all system lists
void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : m_systems)
	{
		auto const& system = pair.second;
		// Set used to avoid checking if entity exists before erasing
		system->m_entities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : m_systems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = m_signatures[type];

		// Entity signature matches system signature - insert into set
		if ((entitySignature & systemSignature) == systemSignature)
		{
			system->m_entities.insert(entity);
		}
		// Entity signature does not match system signature - erase from set
		else
		{
			system->m_entities.erase(entity);
		}
	}
}

void SystemManager::Update()
{
	// Update for all systems.
	for (auto const& pair : m_systems)
	{
		if (pair.second->IsActive())
		{
			pair.second->Update();
		}
	}
}