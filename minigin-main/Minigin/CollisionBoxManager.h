#pragma once
#include <vector>

#include "CollisionBoxComponent.h"
#include "Singleton.h"
#include <SDL_rect.h>

namespace dae
{
	class CollisionBoxManager : public Singleton<CollisionBoxManager>
	{
	public:
		CollisionBoxManager() = default;
		virtual ~CollisionBoxManager() = default;
		CollisionBoxManager(const CollisionBoxManager& other) = delete;
		CollisionBoxManager(CollisionBoxManager&& other) = delete;
		CollisionBoxManager& operator=(const CollisionBoxManager& other) = delete;
		CollisionBoxManager& operator=(CollisionBoxManager&& other) = delete;

		void AddCollisionBox(dae::GameObject* owner, CollisionBoxComponent* box);
		void RemoveCollisionBox(CollisionBoxComponent* box);

		std::vector<CollisionBoxComponent*> GetAllWallColliders() const;

		bool CheckForCollision(CollisionBoxComponent* box);
		CollisionBoxComponent* CheckForCollisionComponent(CollisionBoxComponent* box);
		bool CheckForOverlapEnemy(CollisionBoxComponent* box);

		bool Raycast(glm::vec2 startpos, glm::vec2 direction, dae::CollisionBoxComponent* collisionbox);

	private:
		std::vector<CollisionBoxComponent*> m_pCollisonBoxes;
		std::vector<dae::GameObject*> m_pOwners;
	};

}