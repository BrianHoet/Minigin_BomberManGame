#include "PlayerBomberManPrefab.h"

#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

PlayerBomberManPrefab::PlayerBomberManPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos)
{
	auto GameObjBomberManTex = std::make_shared<dae::GameObject>("BomberMan");
	GameObjBomberManTex->SetRelativePosition(PlayerStartPos);
	auto TextureCpBomberman = std::make_shared<dae::TextureComponent>(GameObjBomberManTex.get());
	TextureCpBomberman->SetTexture("BomberMan_Running.png");
	GameObjBomberManTex->AddComponent(TextureCpBomberman);

	dae::MoveCommand* moveCommandUp = new dae::MoveCommand{ GameObjBomberManTex.get(), up };
	dae::MoveCommand* moveCommandDown = new dae::MoveCommand{ GameObjBomberManTex.get(), down };
	dae::MoveCommand* moveCommandLeft = new dae::MoveCommand{ GameObjBomberManTex.get(), left };
	dae::MoveCommand* moveCommandRight = new dae::MoveCommand{ GameObjBomberManTex.get(), right };
	//dae::PlaceBomb* PlaceBombCommand = new dae::PlaceBomb{ GameObjBomberManTex.get(), GameObjBomb.get() ,glm::vec3{0,0,0} };

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);


	scene.Add(GameObjBomberManTex);
}
