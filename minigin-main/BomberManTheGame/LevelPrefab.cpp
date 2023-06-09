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

		// Get the number of blocks to add (half the size of m_PathPositions)
		size_t numBlocksToAdd = halfSize;

		// Randomly select path positions and add blocks
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, m_PathPositions.size() - 1);

		std::vector<bool> selectedPositions(m_PathPositions.size(), false); // Keep track of selected positions

		for (size_t i = 0; i < numBlocksToAdd; ++i)
		{
			// Find a random unselected position within the vector
			size_t randomIndex = dist(gen);
			while (selectedPositions[randomIndex])
			{
				randomIndex = dist(gen);
			}

			// Mark the position as selected
			selectedPositions[randomIndex] = true;

			// Get the position from the selected index
			glm::vec2 randomPathPosition = m_PathPositions[randomIndex];

			// Check if the random path position is near any spawn position
			bool isNearSpawnPosition = false;
			const float distanceThreshold = 16.f; // Adjust the threshold as needed

			for (const auto& spawnPos : m_SpawnPositions)
			{
				// Check if the random path position is within a certain distance of any spawn position
				if (glm::distance(randomPathPosition, spawnPos) <= distanceThreshold)
				{
					isNearSpawnPosition = true;
					break;
				}
			}

			// Skip this iteration if the random path position is near any spawn position
			if (isNearSpawnPosition)
				continue;

			// Create the block on top of the randomly selected path position
			auto pBreakBlock = std::make_shared<dae::GameObject>();
			pBreakBlock->SetTag("Breakable");

			//Texture
			auto pBreakTexture = std::make_shared<dae::TextureComponent>(pBreakBlock.get());
			pBreakBlock->AddComponent(pBreakTexture);
			pBreakTexture->SetTexture("BreakableWall.png"); // Replace "BlockTexture.png" with the actual texture for the block

			//Collision
			auto pBreakCollider = std::make_shared<dae::CollisionBoxComponent>(pBreakBlock.get());
			pBreakBlock->AddComponent(pBreakCollider);
			pBreakCollider->SetRenderCollisionBox(true);
			//Pos
			pBreakBlock->SetRelativePosition({ randomPathPosition.x, randomPathPosition.y }); // Position it above the path block

			scene.Add(pBreakBlock);
		}
	}
	else
	{
		// Handle the case when there are no path positions available
		std::cout << "No path positions available." << std::endl;
	}

}
