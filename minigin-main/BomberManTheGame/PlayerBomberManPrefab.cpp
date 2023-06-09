#include "PlayerBomberManPrefab.h"

#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

#include "CollisionBoxComponent.h"
#include "CommandsBomberMan.h"

dae::PlayerBomberManPrefab::PlayerBomberManPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<dae::GameObject> Bomb)
{
	auto GameObjBomberManTex = std::make_shared<dae::GameObject>("BomberMan");
	GameObjBomberManTex->SetRelativePosition(PlayerStartPos);

	//Texture
	auto TextureCpBomberman = std::make_shared<dae::TextureComponent>(GameObjBomberManTex.get());
	TextureCpBomberman->SetTexture("BomberMan_Running.png");
	GameObjBomberManTex->AddComponent(TextureCpBomberman);

	////transform
	//auto transform = std::make_shared<dae::Transform>(GameObjBomberManTex.get());
	//transform->SetPosition(GameObjBomberManTex->GetWorldPosition().x, GameObjBomberManTex->GetWorldPosition().y);
	//GameObjBomberManTex->AddComponent(transform);

	//Counter
	auto CounterComp = std::make_shared<CountDownTimer>(GameObjBomberManTex.get() ,3.f);
	GameObjBomberManTex->AddComponent(CounterComp);

	//Collision
	auto Collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBomberManTex.get());
	GameObjBomberManTex->AddComponent(Collider);


	//Movement
	BMCommands::BMMovement* moveCommandUp = new BMCommands::BMMovement{ GameObjBomberManTex.get(), up };
	BMCommands::BMMovement* moveCommandDown = new BMCommands::BMMovement{ GameObjBomberManTex.get(), down };
	BMCommands::BMMovement* moveCommandLeft = new BMCommands::BMMovement{ GameObjBomberManTex.get(), left };
	BMCommands::BMMovement* moveCommandRight = new BMCommands::BMMovement{ GameObjBomberManTex.get(), right };

	
	BMCommands::BMPlaceBomb* PlaceBombCommand = new BMCommands::BMPlaceBomb{ GameObjBomberManTex.get(), Bomb.get() , CounterComp};

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_X, PlaceBombCommand);

	scene.Add(GameObjBomberManTex);
}
