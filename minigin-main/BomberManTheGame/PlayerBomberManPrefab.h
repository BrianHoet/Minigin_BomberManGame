#pragma once
#include "GameObject.h"
#include "LevelPrefab.h"
#include "Scene.h"

namespace dae
{

	class PlayerBomberManPrefab final
	{
	public:
		PlayerBomberManPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<dae::GameObject> Bomb, std::shared_ptr<GameObject> background, bool ControllerEnabled);

		~PlayerBomberManPrefab() = default;
		PlayerBomberManPrefab(const PlayerBomberManPrefab& other) = delete;
		PlayerBomberManPrefab(PlayerBomberManPrefab&& other) = delete;
		PlayerBomberManPrefab& operator=(const PlayerBomberManPrefab& other) = delete;
		PlayerBomberManPrefab& operator=(PlayerBomberManPrefab&& other) = delete;

	private:
		const float speed{ 100.f };
		glm::vec2 up = { 0.f,-speed };
		glm::vec2 down = { 0.f,speed };
		glm::vec2 right = { speed,0.f };
		glm::vec2 left = { -speed,0.f };
	};

}