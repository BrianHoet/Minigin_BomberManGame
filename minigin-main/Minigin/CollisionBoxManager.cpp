#include "CollisionBoxManager.h"

void dae::CollisionBoxManager::AddCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.push_back(box);
}

void dae::CollisionBoxManager::RemoveCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
}

bool dae::CollisionBoxManager::CheckForCollision(CollisionBoxComponent* box)
{
    for (const auto& otherBox : m_pCollisonBoxes)
    {
        if(otherBox == box)
            continue;

        if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
            box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
            box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
            box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
        {
            return true;
        }
        else
        return false;
    }
    return false;

}

