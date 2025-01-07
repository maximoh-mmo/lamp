#pragma once
#include "ComponentManager.h"
#include "ecs.h"
#include "entitymanager.h"
#include "systemmanager.h"


/// <summary>
///
///	 Conductor class manages the ECS structure.
///	 Creates and destroys entities, components and systems.
///	 Ensures parity between the manager classes.
///
/// </summary>

class Conductor
{
public:
	void Init();

	// Entity methods
	Entity CreateEntity() const;
	void DestroyEntity(Entity entity);
	void Update() const { m_systemManager->Update(); }

	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		m_componentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		m_componentManager->AddComponent<T>(entity, component);

		auto signature = m_entityManager->GetSignature(entity);
		signature.set(m_componentManager->GetComponentType<T>(), true);
		m_entityManager->SetSignature(entity, signature);

		m_systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		m_componentManager->RemoveComponent<T>(entity);

		auto signature = m_entityManager->GetSignature(entity);
		signature.set(m_componentManager->GetComponentType<T>(), false);
		m_entityManager->SetSignature(entity, signature);

		m_systemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return m_componentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_componentManager->GetComponentType<T>();
	}

	// System methods

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return m_systemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		m_systemManager->SetSignature<T>(signature);
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{
		return m_systemManager->GetSystem<T>();
	}

private:
	std::unique_ptr<ComponentManager> m_componentManager;
	std::unique_ptr<EntityManager> m_entityManager;
	std::unique_ptr<SystemManager> m_systemManager;
};
