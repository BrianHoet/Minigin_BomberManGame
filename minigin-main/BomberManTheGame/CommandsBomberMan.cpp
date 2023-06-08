#include "CommandsBomberMan.h"

#include "CollisionBoxManager.h"
#include "Renderer.h"
#include "TextureComponent.h"

BMCommands::BMMovement::BMMovement(dae::GameObject* owner, const glm::vec2& dir)
{
	m_pGameObject = owner;
	m_Dir = dir;
    m_pCollision = m_pGameObject->GetComponent<dae::CollisionBoxComponent>();
}

void BMCommands::BMMovement::Execute(float deltaTime)
{
    if (m_pGameObject->ReturnDeleting()) return;

    glm::vec2 pos = m_pGameObject->GetRelativePosition();
    glm::vec2 startPos = m_pGameObject->GetRelativePosition();
	startPos.x += m_pCollision->GetCollisionRect().w / 2.0f;
	startPos.y += m_pCollision->GetCollisionRect().h / 2.0f;


    
    glm::vec2 dir = glm::normalize(m_Dir);
    float distance = 16.0f / 2.f;
    const float offset{ 1.f };
    // Check for collision with obstacles
    for (const auto& boxes : dae::CollisionBoxManager::GetInstance().GetAllWallColliders())
    {
    
        if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
            startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
            startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
            startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
        {
            return;
        }
    }
    

    pos.x += m_Dir.x * deltaTime;
    pos.y += m_Dir.y * deltaTime;
    
    m_pGameObject->SetRelativePosition(pos);
}



BMCommands::BMPlaceBomb::BMPlaceBomb(dae::GameObject* owner, dae::GameObject* bomb, std::shared_ptr<CountDownTimer> countdown)
{
    m_pGameObject = owner;
    m_pBomb = bomb;
    m_pcounter = countdown;
}

void BMCommands::BMPlaceBomb::Execute(float /*deltaTime*/)
{

    if (m_pcounter->GetIsDoneCountingDown())
    {
        m_pBomb->SetRelativePosition(m_pGameObject->GetRelativePosition());
        m_pcounter->SetIsDoneCountingDown(false);
    }
    
   
}