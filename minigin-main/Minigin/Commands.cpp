#include "Commands.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "Counter.h"

namespace dae
{
    class HealthComponent;

    MoveCommand::MoveCommand(dae::GameObject* owner, const glm::vec2& dir)
    {
        m_pGameObject = owner;
        m_Dir = dir;
    }

    void MoveCommand::Execute(float deltaTime)
    {
        if (m_pGameObject->ReturnDeleting()) return;

        glm::vec2 pos = m_pGameObject->GetRelativePosition();
        pos.x += m_Dir.x * deltaTime;
        pos.y += m_Dir.y * deltaTime;

        m_pGameObject->SetRelativePosition(pos);
    }

    PlaceBomb::PlaceBomb(dae::GameObject* owner, dae::GameObject* bomb, const glm::vec2& pos)
    {
        m_pGameObject = owner;
        m_pBomb = bomb;
        m_Pos = pos;
    }

    void PlaceBomb::Execute(float /*deltaTime*/)
    {
        
    	m_pBomb->SetRelativePosition(m_pGameObject->GetRelativePosition());
    }


    HealthCommand::HealthCommand(dae::GameObject* owner)
    {
        m_pGameObject = owner;
    }

    void HealthCommand::Execute(float)
    {
        if (m_pGameObject->ReturnDeleting()) return;

        if (auto health = m_pGameObject->GetComponent<dae::HealthComponent>())
        {
            health->SetAmount(0);
        }
    }

    PointCommand::PointCommand(dae::GameObject* gameObj)
    {
        m_pGameObject = gameObj;
    }

    void PointCommand::Execute(float)
    {
        if (!m_pGameObject) return;

        if (auto points = m_pGameObject->GetComponent<dae::PointsComponent>())
        {
            points->ChangeAmount(1);

            m_pGameObject->NotifyObservers(SCORE_ADDED);
        }
    }
    
}