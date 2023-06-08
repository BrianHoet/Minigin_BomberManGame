#pragma once
#include <glm/vec2.hpp>
#include "GameObject.h"

namespace dae
{

    class Command
    {
    public:
        virtual ~Command() = default;
        virtual void Execute(float) = 0;

    protected:
        dae::GameObject* GetGameActor() const { return m_pGameObject; }
        dae::GameObject* m_pGameObject{};

    };

    class MoveCommand : public Command
    {
    private:
        glm::vec2 m_Dir{};
    public:
        MoveCommand(dae::GameObject* owner, const glm::vec2& dir);
        virtual void Execute(float deltaTime) override;
    };


    class HealthCommand : public Command
    {

    public:
        HealthCommand(dae::GameObject* owner);
        virtual void Execute(float) override;
    };

    class PointCommand final : public Command
    {
    public:
        PointCommand(dae::GameObject* gameObj);
        virtual void Execute(float) override;

    };

}