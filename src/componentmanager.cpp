#include "stdafx.h"
#include "componentmanager.h"

void ComponentManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : mComponentArrays)
	{
		auto const& component = pair.second;

		component->EntityDestroyed(entity);

	}
}