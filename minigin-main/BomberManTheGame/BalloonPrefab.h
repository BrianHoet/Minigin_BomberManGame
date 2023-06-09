#pragma once
#include "LevelPrefab.h"
#include "Scene.h"

namespace dae
{

	class BalloonPrefab
	{
	public:
		BalloonPrefab(dae::Scene& scene, const dae::LevelPrefab& level,glm::vec2 startpos);

		~BalloonPrefab() = default;
		BalloonPrefab(const BalloonPrefab& other) = delete;
		BalloonPrefab(BalloonPrefab&& other) = delete;
		BalloonPrefab& operator=(const BalloonPrefab& other) = delete;
		BalloonPrefab& operator=(BalloonPrefab&& other) = delete;

	private:

	};
}
