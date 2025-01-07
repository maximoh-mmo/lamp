#pragma once
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "ecs.h"

class System;

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSignature(Signature signature);

	template<typename T>
	std::shared_ptr<T> GetSystem();

	void EntityDestroyed(Entity entity);
	void EntitySignatureChanged(Entity entity, Signature entitySignature);
	void Update();

private:
	// Type to Signature Map
	std::unordered_map<const char*, Signature> m_signatures{};

	// Type to System Map
	std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
};

template <typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();

	if (m_systems.find(typeName) != m_systems.end())
		throw std::logic_error("Registering system more than once.");

	// Create a pointer to the system and return it so it can be used externally
	auto system = std::make_shared<T>();
	m_systems.insert({ typeName, system });
	return system;
}

template <typename T>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	if (m_systems.find(typeName) == m_systems.end())
		throw std::logic_error("System used before registered.");

	// Set the signature for this system
	m_signatures.insert({ typeName, signature });
}

template <typename T>
std::shared_ptr<T> SystemManager::GetSystem()
{
	const char* typeName = typeid(T).name();

	if (m_systems.find(typeName) == m_systems.end())
		throw std::logic_error("System not found.");

	return std::static_pointer_cast<T>(m_systems.find(typeName)->second);
}
