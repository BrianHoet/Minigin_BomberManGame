#include "LevelPrefab.h"

#include "CollisionBoxComponent.h"
#include "ResourceManager.h"
#include "TextureComponent.h"

dae::LevelPrefab::LevelPrefab(dae::Scene& scene)
{
	constexpr int width{ 640 };
	constexpr int height{ 480 };
	std::vector<int> mapVector = dae::ResourceManager::GetInstance().ParseMapTxt("../Data/level_02.txt");
	auto grid = ResourceManager::GetInstance().ReturnGrid();

	glm::vec2 startPos{ (width / 2) - ((float(grid.first) / 2.f) * 16), (height / 2) - ((float(grid.second)/ 2.f) * 16) };
	glm::vec2 pos{ startPos.x, startPos.y };

	for (size_t i = 0; i < mapVector.size(); ++i)
	{
		auto pBlock = std::make_shared<dae::GameObject>();
		auto pTexture = std::make_shared<dae::TextureComponent>(pBlock.get());
		

		pBlock->AddComponent(pTexture);
		pBlock->SetRelativePosition({ pos.x, pos.y });

		pTexture->SetTexture("Path.png");

		auto Collider = std::make_shared<CollisionBoxComponent>(pBlock.get());

		scene.Add(pBlock);

		const glm::vec2 size{ pTexture->GetSize() };

		switch (mapVector[i])
		{
		case 0:
			pTexture->SetTexture("UnbreakableWall.png");
			pBlock->SetTag("Wall");
			pBlock->AddComponent(Collider);
			m_WallPositions.push_back(glm::vec2{pos.x, pos.y});
			break;
		case 1:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			break;
		case 2:
			pTexture->SetTexture("Spawn.png");
			pBlock->SetTag("Spawn");
			m_SpawnPositions.push_back(glm::vec2{ pos.x, pos.y });
			break;
			//case 3:
			//	//pTexture->SetTexture("Resources/Level/teleport.png");
			//	//pBlock->SetTag("Teleport");
			//	//m_pTeleport.push_back(pBlock.get());
			//	break;
			default:
				scene.Add(pBlock);
				break;
		}
		pos.x += size.x;

		;
		std::cout << grid.first << ", " << grid.second << '\n';

		if ((i + 1) % grid.first == 0)
		{
			pos.x = startPos.x;
			pos.y += size.y;
		}
	}
}

std::vector<glm::vec2> dae::LevelPrefab::GetSpawnPosition() const
{
	return m_SpawnPositions;
}

std::vector<glm::vec2> dae::LevelPrefab::GetWallPositions() const
{
	return m_WallPositions;
}
