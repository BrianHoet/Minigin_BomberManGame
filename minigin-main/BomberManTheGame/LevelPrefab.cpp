#include "LevelPrefab.h"

#include "CollisionBoxComponent.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include <random>

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
			break;
		case 1:
			pTexture->SetTexture("Path.png");
			pBlock->SetTag("Path");
			m_PathPositions.push_back(glm::vec2{ pos.x, pos.y});
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


		if ((i + 1) % grid.first == 0)
		{
			pos.x = startPos.x;
			pos.y += size.y;
		}

		// Debug statements
		std::cout << "Path Positions Size: " << m_PathPositions.size() << std::endl;
	}
}

std::vector<glm::vec2> dae::LevelPrefab::GetSpawnPosition() const
{
	return m_SpawnPositions;
}

void dae::LevelPrefab::AddRandomBreakableBlocks(dae::Scene& scene)
{
	if (!m_PathPositions.empty())
	{
		// Calculate half of the vector size
		size_t halfSize = m_PathPositions.size() / 2;

		// Randomly select an index within the first half of the vector
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, halfSize - 1);
		size_t randomIndex = dist(gen);

		// Get the position from the selected index
		glm::vec2 randomPathPosition = m_PathPositions[randomIndex];

		// Create the block on top of the randomly selected path position
		auto pBreakBlock = std::make_shared<dae::GameObject>();
		auto pBreakTexture = std::make_shared<dae::TextureComponent>(pBreakBlock.get());

		pBreakBlock->AddComponent(pBreakTexture);
		pBreakBlock->SetRelativePosition({ randomPathPosition.x, randomPathPosition.y - 16.f }); // Position it above the path block

		pBreakTexture->SetTexture("BreakableWall.png"); // Replace "BlockTexture.png" with the actual texture for the block

		scene.Add(pBreakBlock);
	}
	else
	{
		// Handle the case when there are no path positions available
		std::cout << "No path positions available." << std::endl;
	}
}
