#include "Level.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "TextureComponent.h"

Level::Level(const std::string& file)
{

	LevelCreation(file);

}

std::vector<glm::vec2> Level::Getspawnpoints()
{
    return m_SpawnPos;
}

void Level::LevelCreation(const std::string& file)
{

    constexpr int width{ 640 };
    constexpr int height{ 480 };

	std::vector<int> mapVector = dae::ResourceManager::GetInstance().ParseMapTxt(file);

    constexpr glm::vec2 startPos{ (width/2) - ((33.f/2.f)*16),(height/2) - ((13.f/2.f)*16)};
    glm::vec2 pos{ startPos };

    for (size_t i{}; i < mapVector.size(); ++i)
    {
        auto pBlock = std::make_shared<GameObject>();
        auto pTexture = std::make_shared<dae::TextureComponent>(pBlock.get());
        AddChild(pBlock.get());
        pBlock->AddComponent(pTexture);
        pBlock->SetRelativePosition({ pos.x, pos.y });
        
        pTexture->SetTexture("Path.png");

       const glm::vec2 size{ pTexture->GetSize() };

        switch (mapVector[i])
        {
        case 0:
            pTexture->SetTexture("UnbreakableWall.png");
            m_pLevelGameObjects.push_back(std::move(pBlock));
            //pBlock->SetTag("Wall");
           
            break;
        case 1:
            pTexture->SetTexture("Path.png");
            break;
        case 2:
            pTexture->SetTexture("Spawn.png");
            m_SpawnPos.push_back(glm::vec2{ pos.x, pos.y});
            break;
        case 3:
            //pTexture->SetTexture("Resources/Level/teleport.png");
            //pBlock->SetTag("Teleport");
            //m_pTeleport.push_back(pBlock.get());
            break;
        default:
           // m_pLevelGameObjects.push_back(std::move(pBlock));
            break;
        }
        m_pLevelGameObjects.push_back(std::move(pBlock));

        pos.x += size.x;

        if ((i + 1) % 33 == 0)
        {
            std::cout << '\n';
            pos.x = startPos.x;
            pos.y += size.y;
        }
    }
}
