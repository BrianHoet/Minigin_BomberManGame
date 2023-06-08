#include "CollisionBoxComponent.h"

#include "CollisionBoxManager.h"
#include "GameObject.h"

dae::CollisionBoxComponent::CollisionBoxComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pTransform = m_pOwner->GetComponent<Transform>();
	m_CollisionBox.w = static_cast<int>(m_pOwner->GetComponent<TextureComponent>()->GetSize().x);
	m_CollisionBox.h = static_cast<int>(m_pOwner->GetComponent<TextureComponent>()->GetSize().y);

	CollisionBoxManager::GetInstance().AddCollisionBox(this);
}

void dae::CollisionBoxComponent::Update(float)
{
	m_CollisionBox.x = static_cast<int>(m_pTransform->GetPosition().x);
	m_CollisionBox.y = static_cast<int>(m_pTransform->GetPosition().y);

}

void dae::CollisionBoxComponent::Render() const
{
}

SDL_Rect dae::CollisionBoxComponent::GetCollisionRect() const
{
	return m_CollisionBox;
}
