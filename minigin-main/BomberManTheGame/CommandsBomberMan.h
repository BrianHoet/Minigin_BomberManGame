#pragma once
#include "CollisionBoxComponent.h"
#include "Commands.h"
#include "CountDownTimer.h"
#include "LevelPrefab.h"
#include "ScreenManager.h"
#include "ScreenManager.h"

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

	class BMPSwitchGame : public dae::Command
	{
	private:
		std::shared_ptr<dae::GameObject> m_pScreen{};
		dae::ScreenManager* m_pScreenManager;
	public:
		BMPSwitchGame(std::shared_ptr<dae::GameObject> owner, dae::ScreenManager* screenmanager);
		virtual void Execute(float) override;

	};


}
