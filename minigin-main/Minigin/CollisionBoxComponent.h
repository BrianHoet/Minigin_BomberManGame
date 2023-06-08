#pragma once
#include <SDL_rect.h>
#include "SDL.h"

#include "BaseComponent.h"
#include "TextureComponent.h"
#include "Transform.h"


namespace dae
{

	class CollisionBoxComponent : public dae::BaseComponent
	{
	public:

		CollisionBoxComponent(dae::GameObject* owner);
		virtual ~CollisionBoxComponent();
		CollisionBoxComponent(const CollisionBoxComponent& other) = delete;
		CollisionBoxComponent(CollisionBoxComponent&& other) = delete;
		CollisionBoxComponent& operator=(const CollisionBoxComponent& other) = delete;
		CollisionBoxComponent& operator=(CollisionBoxComponent&& other) = delete;

		virtual void Update(float) override;
		virtual void Render() const override;
		SDL_Rect GetCollisionRect() const;
		

	private:
		SDL_Rect m_CollisionBox;
		Transform* m_pTransform;
		TextureComponent* m_pTexture;
	};

}
