#pragma once
#include "CollisionBoxComponent.h"
#include "Commands.h"
#include "CountDownTimer.h"
#include "LevelPrefab.h"

namespace BMCommands
{

	class BMMovement : public dae::Command
	{
	private:
		glm::vec2 m_Dir{};
		dae::CollisionBoxComponent* m_pCollision;
	public:
		BMMovement(dae::GameObject* owner, const glm::vec2& dir);
		virtual void Execute(float deltaTime) override;
	};

	class BMPlaceBomb : public dae::Command
	{
	private:
		dae::GameObject* m_pBomb{};
		std::shared_ptr<CountDownTimer> m_pcounter;
	public:
		BMPlaceBomb(dae::GameObject* owner, dae::GameObject* bomb, std::shared_ptr<CountDownTimer> countdown);
		virtual void Execute(float deltaTime) override;

	};

}
