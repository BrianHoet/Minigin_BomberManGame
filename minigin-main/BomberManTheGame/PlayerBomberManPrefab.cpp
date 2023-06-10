#include "PlayerBomberManPrefab.h"

#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

#include "CollisionBoxComponent.h"
#include "CommandsBomberMan.h"
#include "Counter.h"

dae::PlayerBomberManPrefab::PlayerBomberManPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<dae::GameObject> Bomb)
{
	auto GameObjBomberman = std::make_shared<dae::GameObject>("Player_01");
	GameObjBomberman->SetRelativePosition(PlayerStartPos);

	//Texture
	auto TextureCpBomberman = std::make_shared<dae::TextureComponent>(GameObjBomberman.get());
	TextureCpBomberman->SetTexture("BomberMan_Running.png");
	GameObjBomberman->AddComponent(TextureCpBomberman);

	////transform
	//auto transform = std::make_shared<dae::Transform>(GameObjBomberManTex.get());
	//transform->SetPosition(GameObjBomberManTex->GetWorldPosition().x, GameObjBomberManTex->GetWorldPosition().y);
	//GameObjBomberManTex->AddComponent(transform);

	//Counter
	auto CounterComp = std::make_shared<CountDownTimer>(GameObjBomberman.get() ,3.f);
	GameObjBomberman->AddComponent(CounterComp);

	//Collision
	auto Collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBomberman.get());
	GameObjBomberman->AddComponent(Collider);

	//Movement
	BMCommands::BMMovement* moveCommandUp = new BMCommands::BMMovement{ GameObjBomberman.get(), up };
	BMCommands::BMMovement* moveCommandDown = new BMCommands::BMMovement{ GameObjBomberman.get(), down };
	BMCommands::BMMovement* moveCommandLeft = new BMCommands::BMMovement{ GameObjBomberman.get(), left };
	BMCommands::BMMovement* moveCommandRight = new BMCommands::BMMovement{ GameObjBomberman.get(), right };

	
	BMCommands::BMPlaceBomb* PlaceBombCommand = new BMCommands::BMPlaceBomb{ GameObjBomberman.get(), Bomb.get() , CounterComp};

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_X, PlaceBombCommand);

	scene.Add(GameObjBomberman);
}
