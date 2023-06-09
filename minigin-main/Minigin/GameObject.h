#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <iostream>
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class BaseComponent;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);
		

		template <typename T>
		T* GetComponent()
		{
			for (const auto& component : m_pComponents)
			{
				if (typeid(*component) == typeid(T))
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}
		
		void UpdateWorldPos();
		const glm::vec2& GetWorldPosition();

		GameObject* GetParent();
		std::vector<GameObject*> GetChildren() const;
		void SetParent(GameObject* parent);
		void AddChild(GameObject* child);
		

		glm::vec2 GetRelativePosition() const;	
		void SetRelativePosition(glm::vec2 Pos);
		void SetRelativePosition(float Posx, float Posy);

		void FlagIsTrue();
		std::string GetTag() const;
		void SetTag(const std::string& tag);

		void MarkTrueForDeleting();
		bool ReturnDeleting();

		void MakeObserver(std::shared_ptr<Observer> observer);
		void NotifyObservers(Event event);

		GameObject(const std::string& tag = "TagLess");
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	protected:
		std::unique_ptr<Subject> m_pSubject;

	private:
		glm::vec2 m_WorldTransform{};
		glm::vec2 m_RelativeTransform{};

		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};

		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};

		bool m_deletParentFromScene{ false };
		bool m_dirtyFlag{ false };
		std::string m_TagString;

		void RemoveChild(GameObject* childGameObject);
	};
}
