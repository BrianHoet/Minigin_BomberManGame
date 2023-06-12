#pragma once
#include "BaseComponent.h"

namespace dae
{

	class BombComponent : public dae::BaseComponent
	{
	public:

		BombComponent(dae::GameObject* owner);
		~BombComponent() = default;
		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;


	private:

	};

}
