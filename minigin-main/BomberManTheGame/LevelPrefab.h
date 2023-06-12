#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "Scene.h"

namespace dae
{
	class LevelPrefab final
	{
	public:
		LevelPrefab(dae::Scene& scene,const std::string& LevelPath);

		~LevelPrefab() = default;
		LevelPrefab(const LevelPrefab& other) = delete;
		LevelPrefab(LevelPrefab&& other) = delete;
		LevelPrefab& operator=(const LevelPrefab& other) = delete;
		LevelPrefab& operator=(LevelPrefab&& other) = delete;

		std::vector<glm::vec2> GetSpawnPosition() const;
		void AddRandomBreakableBlocks(dae::Scene& scene);

	private:
		std::vector<glm::vec2> m_SpawnPositions{};
		std::vector<glm::vec2> m_PathPositions{};
		std::vector<glm::vec2> m_BlockPositions{};
		bool m_PlacedDoor{ false };
	};

}