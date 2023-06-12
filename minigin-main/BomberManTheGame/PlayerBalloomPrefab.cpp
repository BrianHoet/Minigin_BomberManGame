#include "PlayerBalloomPrefab.h"

#include <SDL_scancode.h>

#include "CollisionBoxComponent.h"
#include "CommandsBomberMan.h"
#include "CountDownTimer.h"
#include "Counter.h"
#include "InputManager.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "UIComponent.h"

dae::PlayerBalloomPrefab::PlayerBalloomPrefab(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, std::shared_ptr<dae::GameObject> Bomb)
{
	auto GameObjBalloom = std::make_shared<dae::GameObject>("Player_02");
	GameObjBalloom->SetRelativePosition(PlayerStartPos);

	//Texture
	auto TextureCpBalloom = std::make_shared<dae::TextureComponent>(GameObjBalloom.get());
	TextureCpBalloom->SetTexture("Balloon.png");
	GameObjBalloom->AddComponent(TextureCpBalloom);

	////transform
	//auto transform = std::make_shared<dae::Transform>(GameObjBomberManTex.get());
	//transform->SetPosition(GameObjBomberManTex->GetWorldPosition().x, GameObjBomberManTex->GetWorldPosition().y);
	//GameObjBomberManTex->AddComponent(transform);

	//Counter
	auto CounterComp = std::make_shared<CountDownTimer>(GameObjBalloom.get(), 3.f);
	GameObjBalloom->AddComponent(CounterComp);

	//Collision
	auto Collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBalloom.get());
	GameObjBalloom->AddComponent(Collider);

	//Movement
	std::shared_ptr<BMCommands::BMMovement> moveCommandUp = std::make_shared<BMCommands::BMMovement>(GameObjBalloom.get(), up);
	std::shared_ptr<BMCommands::BMMovement> moveCommandDown = std::make_shared<BMCommands::BMMovement>(GameObjBalloom.get(), down);
	std::shared_ptr<BMCommands::BMMovement> moveCommandLeft = std::make_shared<BMCommands::BMMovement>(GameObjBalloom.get(), left);
	std::shared_ptr<BMCommands::BMMovement> moveCommandRight = std::make_shared<BMCommands::BMMovement>(GameObjBalloom.get(), right);

	std::shared_ptr<BMCommands::BMPlaceBomb> PlaceBombCommand = std::make_shared<BMCommands::BMPlaceBomb>(GameObjBalloom.get(), Bomb.get(), CounterComp);

	int controller1Index{ 1 };
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

	auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBalloom.get(), 4);
	GameObjBalloom->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBalloom.get(), 0);
	GameObjBalloom->AddComponent(pPoints);

	//HealthCommand* dieCommand = new HealthCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	GameObjBalloom->MakeObserver(pUIObserver);

	//Lives Display
	auto BalloomLivesObj = std::make_shared<dae::GameObject>("BomberMan");
	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		"Lives", BalloomLivesObj.get());
	BalloomLivesObj->SetRelativePosition({ 5, 400 });
	BalloomLivesObj->AddComponent(textBomberManLives);
	background->AddChild(BalloomLivesObj.get());
	scene.Add(BalloomLivesObj);

	//Points Display
	auto BalloonPointsObj = std::make_shared<dae::GameObject>("BomberMan");
	auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		"Points", BalloonPointsObj.get());
	BalloonPointsObj->SetRelativePosition({ 5, 420 });
	BalloonPointsObj->AddComponent(textBluePoints);
	background->AddChild(BalloonPointsObj.get());
	scene.Add(BalloonPointsObj);


	scene.Add(GameObjBalloom);
}
