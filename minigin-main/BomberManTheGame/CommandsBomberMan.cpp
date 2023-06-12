#include "CommandsBomberMan.h"

#include "CollisionBoxManager.h"
#include "InputManager.h"
#include "ServiceLocator.h"

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

BMCommands::BMPlaceBomb::BMPlaceBomb(dae::GameObject* owner, dae::GameObject* bomb, std::shared_ptr<dae::CountDownTimer> countdown)
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



BMCommands::BMPSwitchGame::BMPSwitchGame(std::shared_ptr<dae::GameObject> owner, dae::GameObject* text, const int& currentScreen, dae::ScreenManager* screen)
	:m_pScreen{owner},
    m_pTextMode{text},
    m_CurrentScreen{ currentScreen },
	m_pScreenManager{ screen }
{
}

void BMCommands::BMPSwitchGame::Execute(float)
{
    if (GetKeyPressed()) return;

    auto text = m_pTextMode->GetComponent<dae::TextComponent>();
    //m_pScreenManager->SwitchScreens();
    std::cout << m_CurrentScreen << '\n';

    switch (m_CurrentScreen)
    {
    case 0:
        m_CurrentScreen = 1;
        text->SetText("Coop");
        break;

    case 1:
        m_CurrentScreen = 2;
        text->SetText("Versus");
        break;

    case 2:
        m_CurrentScreen = 0;
        text->SetText("Single");
        break;
    }

    dae::servicelocator::get_sound_system().playSound(0, 5.f);
    m_pScreenManager->SetCurrentEnum(m_CurrentScreen);

    SetKeyPressed(true);
}

BMCommands::AcceptGameMode::AcceptGameMode(std::shared_ptr<dae::GameObject> owner, dae::ScreenManager* screen)
	:m_pScreen{owner},
	m_pScreenManager{screen}
{
}

void BMCommands::AcceptGameMode::Execute(float)
{
    if (m_Pressed) return;
    if (GetKeyPressed()) return;


    if(m_pScreenManager != nullptr)
    {
    m_pScreenManager->CreateAppropriateScene();
    SetKeyPressed(true);
    }

    m_Pressed = true;
    

    //dae::InputManager::GetInstance().UnBindAllKeys();
}
