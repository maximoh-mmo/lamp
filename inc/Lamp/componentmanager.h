#pragma once
#include <memory>
#include "componentarray.h"
#include "icomponentarray.h"
#include "ecs.h"

class ComponentManager
{
public:
	// Declarations
	template<typename T>
	void RegisterComponent();

	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	void AddComponent(Entity entity, T component);

	template<typename T>
	void RemoveComponent(Entity entity);

	template<typename T>
	T& GetComponent(Entity entity);

	void EntityDestroyed(Entity entity);

private:
	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
	ComponentType mNextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray();
};

// Definitions
template<typename T>
void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();

	assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Error: Attempted to register a component type more than once.");

	mComponentTypes.insert({ typeName, mNextComponentType });
	mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	++mNextComponentType;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(T).name();

	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Error: Attempted to use a component type that has not been registered.");

	return mComponentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<T>()->GetData(entity);
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
	const char* typeName = typeid(T).name();

	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

	return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
}
