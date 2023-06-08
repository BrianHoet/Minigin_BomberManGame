#pragma once
#include <SDL_rect.h>
#include "SDL.h"

#include "BaseComponent.h"
#include "TextureComponent.h"
#include "Transform.h"


namespace dae
{

	class CollisionBoxComponent : public BaseComponent
	{
	public:

		CollisionBoxComponent(GameObject* owner);
		virtual ~CollisionBoxComponent() = default;
		CollisionBoxComponent(const CollisionBoxComponent& other) = delete;
		CollisionBoxComponent(CollisionBoxComponent&& other) = delete;
		CollisionBoxComponent& operator=(const CollisionBoxComponent& other) = delete;
		CollisionBoxComponent& operator=(CollisionBoxComponent&& other) = delete;

		virtual void Update(float) override;
		virtual void Render() const override;
		SDL_Rect GetCollisionRect() const;

		GameObject* GetOwner() const;

	private:
		SDL_Rect m_CollisionBox;
	};

}
