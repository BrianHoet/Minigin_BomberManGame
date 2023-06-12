#include "BombComponent.h"

#include <memory>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "TextureComponent.h"


dae::BombComponent::BombComponent(dae::GameObject* owner)
{

	m_pOwner = owner;

	auto GameObjBomb = std::make_shared<dae::GameObject>();
	GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
	auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
	TextureBomb->SetTexture("Bomb_01.png");
	GameObjBomb->AddComponent(TextureBomb);
}
