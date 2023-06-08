#include "CollisionBoxManager.h"

#include "GameObject.h"

void dae::CollisionBoxManager::AddCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.push_back(box);
}

void dae::CollisionBoxManager::RemoveCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllWallColliders() const
{
    std::vector<dae::CollisionBoxComponent*> WallVec{};
    for (const auto& otherBox : m_pCollisonBoxes)
    {

        if(otherBox->GetOwner()->GetTag() == "Wall")
        {
            WallVec.push_back(otherBox);
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