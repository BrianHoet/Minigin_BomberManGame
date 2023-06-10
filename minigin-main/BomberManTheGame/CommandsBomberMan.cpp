#include "CommandsBomberMan.h"

#include "CollisionBoxManager.h"

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

    if(!dae::CollisionBoxManager::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision))
    {
        return;
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



BMCommands::BMPSwitchGame::BMPSwitchGame(std::shared_ptr<dae::GameObject> owner, dae::ScreenManager* screenmanager)
	:m_pScreen(owner),
    m_pScreenManager(screenmanager)
{
}

void BMCommands::BMPSwitchGame::Execute(float)
{
    m_pScreenManager->SwitchScreens();
}
