#include "CollisionBoxManager.h"

#include "GameObject.h"

void dae::CollisionBoxManager::AddCollisionBox(dae::GameObject* owner, CollisionBoxComponent* box)
{
    m_pOwners.push_back(owner);
	m_pCollisonBoxes.push_back(box);
}

void dae::CollisionBoxManager::RemoveCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllWallColliders() const
{
    std::vector<dae::CollisionBoxComponent*> WallVec{};
    for (const auto& Owners : m_pOwners)
    {
	    for (const auto& otherbox : m_pCollisonBoxes)
	    {
            if (Owners->GetTag() == "Wall" || Owners->GetTag() == "Breakable")
            {
                WallVec.push_back(otherbox);
            }
	    }
    }

    return WallVec;
}

bool dae::CollisionBoxManager::CheckForCollision(CollisionBoxComponent* box)
{
    for (const auto& otherBox : m_pCollisonBoxes)
    {
        if (otherBox == box)
            continue;

        if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
            box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
            box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
            box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
        {
            return true;
        }
    }

    return false;


}

dae::CollisionBoxComponent* dae::CollisionBoxManager::CheckForCollisionComponent(CollisionBoxComponent* box)
{
    for (const auto& otherBox : m_pCollisonBoxes)
    {
        if (otherBox == box)
            continue;

        if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
            box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
            box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
            box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
        {
            return otherBox;
        }
    }
    return nullptr;
}