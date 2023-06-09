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

bool dae::CollisionBoxManager::Raycast(glm::vec2 startpos, glm::vec2 direction, dae::CollisionBoxComponent* collisionbox)
{
    glm::vec2 startPos = startpos;
    startPos.x += collisionbox->GetCollisionRect().w / 2.0f;
    startPos.y += collisionbox->GetCollisionRect().h / 2.0f;


    glm::vec2 dir = glm::normalize(direction);
    float distance = collisionbox->GetCollisionRect().w / 2.f;
    const float offset{ 2.f };
    // Check for collision with obstacles
    for (const auto& boxes : GetAllWallColliders())
    {
        if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
            startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
            startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
            startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
        {
            return false;
        }
    }
    return true;
}
