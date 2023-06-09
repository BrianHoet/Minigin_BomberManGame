#include "CollisionBoxComponent.h"

#include "CollisionBoxManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::CollisionBoxComponent::CollisionBoxComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_CollisionBox.w = static_cast<int>(m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().x);
	m_CollisionBox.h = static_cast<int>(m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().y);

	CollisionBoxManager::GetInstance().AddCollisionBox(m_pOwner, this);
}

void dae::CollisionBoxComponent::Update(float)
{
	m_CollisionBox.x = static_cast<int>(m_pOwner->GetWorldPosition().x);
	m_CollisionBox.y = static_cast<int>(m_pOwner->GetWorldPosition().y);

	//std::cout << CollisionBoxManager::GetInstance().CheckForCollision(this) << "\n";
}

void dae::CollisionBoxComponent::Render() const
{
	if(m_RenderCollisionBox)
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer() ,&m_CollisionBox);
}

SDL_Rect dae::CollisionBoxComponent::GetCollisionRect() const
{
	return m_CollisionBox;
}

dae::GameObject* dae::CollisionBoxComponent::GetOwner() const
{
	return m_pOwner;
}
