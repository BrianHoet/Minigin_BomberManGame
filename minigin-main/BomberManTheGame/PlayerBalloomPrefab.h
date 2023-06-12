#pragma once
#include "GameObject.h"
#include "Scene.h"

namespace dae
{
	class PlayerBalloomPrefab
	{
	public:
		PlayerBalloomPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background,std::shared_ptr<dae::GameObject> Bomb);

		~PlayerBalloomPrefab() = default;
		PlayerBalloomPrefab(const PlayerBalloomPrefab& other) = delete;
		PlayerBalloomPrefab(PlayerBalloomPrefab&& other) = delete;
		PlayerBalloomPrefab& operator=(const PlayerBalloomPrefab& other) = delete;
		PlayerBalloomPrefab& operator=(PlayerBalloomPrefab&& other) = delete;

	private:
		const float speed{ 100.f };
		glm::vec2 up = { 0.f,-speed };
		glm::vec2 down = { 0.f,speed };
		glm::vec2 right = { speed,0.f };
		glm::vec2 left = { -speed,0.f };
	};

}