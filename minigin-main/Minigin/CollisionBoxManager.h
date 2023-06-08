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

		void AddCollisionBox(CollisionBoxComponent* box);
		void RemoveCollisionBox(CollisionBoxComponent* box);

		std::vector<CollisionBoxComponent*> GetAllWallColliders() const;

		bool CheckForCollision(CollisionBoxComponent* box);
		CollisionBoxComponent* CheckForCollisionComponent(CollisionBoxComponent* box);

	private:
		std::vector<CollisionBoxComponent*> m_pCollisonBoxes;
	};

}