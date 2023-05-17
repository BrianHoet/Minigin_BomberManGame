#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

namespace dae
{
	void GameObject::Update(float deltaTime)
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->Update(deltaTime);
		}

		for (auto child : m_pChildren)
		{
			child->Update(deltaTime);
		}
	}

	void GameObject::FixedUpdate(float deltaTime)
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->FixedUpdate(deltaTime);
		}

		for (auto child : m_pChildren)
		{
			child->FixedUpdate(deltaTime);
		}
	}

	void GameObject::Render() const
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->Render();
		}

		for(auto child : m_pChildren)
		{
			child->Render();
		}
	}

	void GameObject::UpdateWorldPos()
	{
		if (m_dirtyFlag)
		{
			if (m_pParent == nullptr)
				m_WorldTransform = m_RelativeTransform;
			else
				m_WorldTransform = m_pParent->GetWorldPosition() + m_RelativeTransform;

			m_dirtyFlag = false;
		}
	}

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_pComponents.push_back(component);
	}

	void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
	}

	GameObject* GameObject::GetParent()
	{
		return m_pParent;
	}

	std::vector<GameObject*> GameObject::GetChildren() const
	{
		return m_pChildren;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if(m_pParent)
		{
			m_pParent->RemoveChild(this);
		}
		m_pParent = parent;

		UpdateWorldPos();

	}

	void GameObject::AddChild(GameObject* child)
	{
		m_pChildren.push_back(child);
		child->SetParent(this);
	}

	void GameObject::RemoveChild(GameObject* childGameObject)
	{
		m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), childGameObject), m_pChildren.end());
	}

	const glm::vec2& GameObject::GetWorldPosition()
	{
		if (m_dirtyFlag)
			UpdateWorldPos();
		return m_WorldTransform;
	}

	glm::vec2 GameObject::GetRelativePosition() const
	{
		return m_RelativeTransform;
	}

	void GameObject::SetRelativePosition(glm::vec2 Pos)
	{
		m_RelativeTransform = Pos;

		if(m_pParent == nullptr)
		{
			m_WorldTransform = m_RelativeTransform;
		}

		FlagIsTrue();
	}

	void GameObject::FlagIsTrue()
	{
		m_dirtyFlag = true;
		for (auto child : m_pChildren)
		{
			child->FlagIsTrue();
		}
	}

	std::string GameObject::GetTag() const
	{
		return std::string();
	}

	void GameObject::MarkTrueForDeleting()
	{
		m_pSubject->NotifyObservers(PLAYER_DIED);
		m_deletParentFromScene = true;
	}

	bool GameObject::ReturnDeleting()
	{
		return m_deletParentFromScene;
	}

	void GameObject::MakeObserver(std::shared_ptr<Observer> observer)
	{
		m_pSubject = std::make_unique<Subject>(this);
		m_pSubject->AddObserver(observer);
	}

	void GameObject::NotifyObservers(Event event)
	{
		if (!m_pSubject) return;

		m_pSubject->NotifyObservers(event);
	}

	GameObject::GameObject(const std::string& tag)
		:m_TagString{ tag }
	{
	}

	GameObject::~GameObject()
	{
	}
}
