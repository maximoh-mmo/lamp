#pragma once
#include <set>

#include "ecs.h"

class System
{
public:
	virtual ~System() = default;
	virtual void Update() = 0;
	bool IsActive() const { return b_is_enabled_; }
	virtual void SetActive(bool active) { b_is_enabled_ = active; }

	std::set<Entity> m_entities;
private:
	bool b_is_enabled_ = false;
};
