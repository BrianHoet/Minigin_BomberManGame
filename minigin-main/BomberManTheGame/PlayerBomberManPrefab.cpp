#include "PlayerBomberManPrefab.h"

#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

#include "CollisionBoxComponent.h"
#include "CommandsBomberMan.h"
#include "Counter.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "UIComponent.h"

dae::PlayerBomberManPrefab::PlayerBomberManPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<dae::GameObject> Bomb, std::shared_ptr<GameObject> background, bool ControllerEnabled)
{
	auto GameObjBomberman = std::make_shared<dae::GameObject>("Player_01");
	GameObjBomberman->SetRelativePosition(PlayerStartPos);

	//Texture
	auto TextureCpBomberman = std::make_shared<dae::TextureComponent>(GameObjBomberman.get());
	TextureCpBomberman->SetTexture("BomberMan_Running.png");
	GameObjBomberman->AddComponent(TextureCpBomberman);

	//Counter
	auto CounterComp = std::make_shared<CountDownTimer>(GameObjBomberman.get() ,3.f);
	GameObjBomberman->AddComponent(CounterComp);

	//Collision
	auto Collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBomberman.get());
	GameObjBomberman->AddComponent(Collider);

	//Movement
	std::shared_ptr<BMCommands::BMMovement> moveCommandUp = std::make_shared<BMCommands::BMMovement>(GameObjBomberman.get(), up);
	std::shared_ptr<BMCommands::BMMovement> moveCommandDown = std::make_shared<BMCommands::BMMovement>(GameObjBomberman.get(), down);
	std::shared_ptr<BMCommands::BMMovement> moveCommandLeft = std::make_shared<BMCommands::BMMovement>(GameObjBomberman.get(), left);
	std::shared_ptr<BMCommands::BMMovement> moveCommandRight = std::make_shared<BMCommands::BMMovement>(GameObjBomberman.get(), right);

	
	std::shared_ptr<BMCommands::BMPlaceBomb> PlaceBombCommand = std::make_shared<BMCommands::BMPlaceBomb>(GameObjBomberman.get(), Bomb.get(), CounterComp);

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_X, PlaceBombCommand);

	if(ControllerEnabled)
	{
		int controller1Index{ 0 };
		dae::InputManager::GetInstance().AddController(controller1Index);

		dae::Controller::ControllerButton controllerButton{};

		controllerButton = dae::Controller::ControllerButton::DpadUp;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUp);
		controllerButton = dae::Controller::ControllerButton::DpadDown;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDown);
		controllerButton = dae::Controller::ControllerButton::DpadLeft;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeft);
		controllerButton = dae::Controller::ControllerButton::DpadRight;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRight);
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, PlaceBombCommand);
	}

	auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBomberman.get(), 4);
	GameObjBomberman->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBomberman.get(), 0);
	GameObjBomberman->AddComponent(pPoints);

	//std::shared_ptr<HealthCommand> dieCommand = std::make_shared<HealthCommand>(GameObjBomberman.get());
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	GameObjBomberman->MakeObserver(pUIObserver);

	//Lives Display
	auto BomberManLivesObj = std::make_shared<dae::GameObject>("BomberMan");
	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		"Lives", BomberManLivesObj.get());
	BomberManLivesObj->SetRelativePosition({ 5, 340 });
	BomberManLivesObj->AddComponent(textBomberManLives);
	background->AddChild(BomberManLivesObj.get());
	scene.Add(BomberManLivesObj);

	//Points Display
	auto BomberManPointsObj = std::make_shared<dae::GameObject>("BomberMan");
	auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		"Points", BomberManPointsObj.get());
	BomberManPointsObj->SetRelativePosition({ 5, 360 });
	BomberManPointsObj->AddComponent(textBluePoints);
	background->AddChild(BomberManPointsObj.get());
	scene.Add(BomberManPointsObj);


	scene.Add(GameObjBomberman);
}
