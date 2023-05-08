#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include <SDL.h>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Scene.h"
#include <iostream>
#include "GameObject.h"
#include "BaseComponent.h"
#include "FPSCounterComponent.h"
#include "RotationComponent.h"
#include "Commands.h"
#include "Counter.h"
#include "UIComponent.h"
#include "Observer.h"

/*
void ControllerInit(dae::Scene& scene, dae::GameObject* parent)
{
	const float speed{ 100.f };
	//Player 1
	{
		glm::vec3 up = { 0.f,-speed,0.f };
		glm::vec3 down = { 0.f,speed,0.f };
		glm::vec3 right = { speed,0.f,0.f };
		glm::vec3 left = { -speed,0.f,0.f };

		auto GameObjBomberManTex = std::make_shared<dae::GameObject>("BomberMan");
		GameObjBomberManTex->SetRelativePosition(glm::vec3{ 400, 380 ,0 });
		auto TextureCpBomberman = std::make_shared<dae::TextureComponent>(GameObjBomberManTex.get());
		TextureCpBomberman->SetTexture("BomberMan_Running.png");
		GameObjBomberManTex->AddComponent(TextureCpBomberman);

		//MoveCommand* moveCommandUp = new MoveCommand{ GameObjBomberManTex.get(), up };
		//MoveCommand* moveCommandDown = new MoveCommand{ GameObjBomberManTex.get(), down };
		//MoveCommand* moveCommandLeft = new MoveCommand{ GameObjBomberManTex.get(), left };
		//MoveCommand* moveCommandRight = new MoveCommand{ GameObjBomberManTex.get(), right };
		//
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);


		//auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBomberManTex.get(), 3);
		//GameObjBomberManTex->AddComponent(pHealth);

		//auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBomberManTex.get(), 0);
		//GameObjBomberManTex->AddComponent(pPoints);

		//HealthCommand* dieCommand = new HealthCommand{ GameObjBomberManTex.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
		//PointCommand* pointCommand = new PointCommand{ GameObjBomberManTex.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

		//auto pUIObserver = std::make_shared<UI>();
		//GameObjBomberManTex->MakeObserver(pUIObserver);

		parent->AddChild(GameObjBomberManTex.get());

		scene.Add(GameObjBomberManTex);

		//Lives Display
		//auto BomberManLivesObj = std::make_shared<dae::GameObject>("BomberMan");
		//auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		//auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		//	"Lives", BomberManLivesObj.get());
		//BomberManLivesObj->SetRelativePosition({ 5, 310, 0 });
		//BomberManLivesObj->AddComponent(textBomberManLives);
		//parent->AddChild(BomberManLivesObj.get());
		//scene.Add(BomberManLivesObj);

		//Points Display
		//auto BomberManPointsObj = std::make_shared<dae::GameObject>("BomberMan");
		//auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		//	"Points", BomberManPointsObj.get());
		//BomberManPointsObj->SetRelativePosition({ 5, 330, 0 });
		//BomberManPointsObj->AddComponent(textBluePoints);
		//parent->AddChild(BomberManPointsObj.get());
		//scene.Add(BomberManPointsObj);

		//GameObjBomberManTex->NotifyObservers(Update);
	}
	/*
	//Player 2
	{
		glm::vec3 upBallon = { 0.f,-speed * 2.f,0.f };
		glm::vec3 downBallon = { 0.f,speed * 2.f,0.f };
		glm::vec3 rightBallon = { speed * 2.f,0.f,0.f };
		glm::vec3 leftBallon = { -speed * 2.f,0.f,0.f };


		auto GameObjBallonTex = std::make_shared<dae::GameObject>("Ballon");
		GameObjBallonTex->SetRelativePosition(glm::vec3{ 250, 280 ,0 });
		auto TextureCpBallon = std::make_shared<dae::TextureComponent>(GameObjBallonTex.get());

		TextureCpBallon->SetTexture("BomberMan_Ballon.png");
		GameObjBallonTex->AddComponent(TextureCpBallon);

		MoveCommand* moveCommandUpBallon = new MoveCommand{ GameObjBallonTex.get(), upBallon };
		MoveCommand* moveCommandDownBallon = new MoveCommand{ GameObjBallonTex.get(), downBallon };
		MoveCommand* moveCommandLeftBallon = new MoveCommand{ GameObjBallonTex.get(), leftBallon };
		MoveCommand* moveCommandRightBallon = new MoveCommand{ GameObjBallonTex.get(), rightBallon };

		int controller1Index{ 0 };
		dae::InputManager::GetInstance().AddController(controller1Index);

		Controller::ControllerButton controllerButton{};

		controllerButton = Controller::ControllerButton::DpadUp;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUpBallon);
		controllerButton = Controller::ControllerButton::DpadDown;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDownBallon);
		controllerButton = Controller::ControllerButton::DpadLeft;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeftBallon);
		controllerButton = Controller::ControllerButton::DpadRight;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRightBallon);
		scene.Add(GameObjBallonTex);

		//auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBallonTex.get(), 1);
		//GameObjBallonTex->AddComponent(pHealth);
		//
		//auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBallonTex.get(), 0);
		//GameObjBallonTex->AddComponent(pPoints);
		//
		//HealthCommand* dieCommandRed = new HealthCommand{ GameObjBallonTex.get() };
		//controllerButton = Controller::ControllerButton::ButtonY;
		//dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, dieCommandRed);
		//PointCommand* pointCommandRed = new PointCommand{ GameObjBallonTex.get() };
		//controllerButton = Controller::ControllerButton::ButtonA;
		//dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, pointCommandRed);
		//
		//auto pUIObserver = std::make_shared<UI>();
		//GameObjBallonTex->MakeObserver(pUIObserver);

		parent->AddChild(GameObjBallonTex.get());

		//Lives Display
		//auto BallonLivesObj = std::make_shared<dae::GameObject>("Ballon");
		//auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		//auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		//	"Lives", BallonLivesObj.get());
		//BallonLivesObj->SetRelativePosition({ 5, 410, 0 });
		//BallonLivesObj->AddComponent(textBomberManLives);
		//parent->AddChild(BallonLivesObj.get());
		//scene.Add(BallonLivesObj);
		//
		////Points Display
		//auto BallonPointsObj = std::make_shared<dae::GameObject>("Ballon");
		//auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		//	"Points", BallonPointsObj.get());
		//BallonPointsObj->SetRelativePosition({ 5, 430, 0 });
		//BallonPointsObj->AddComponent(textBluePoints);
		//parent->AddChild(BallonPointsObj.get());
		//scene.Add(BallonPointsObj);

		//GameObjBallonTex->NotifyObservers(Update);
	}
	
}
*/

void load()
{
	std::cout << "--How To Play--\n";
	std::cout << "WASD to move character\n";
	std::cout << "O to kill the player\n";
	std::cout << "P to increase points (doens't work)\n";
	std::cout << "Dpad to move secondPlayer\n";
	std::cout << "Y to kill the player\n";
	std::cout << "A to increase points (doens't work)\n";

	
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto GameObjBackGround = std::make_shared<dae::GameObject>();
	auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
	go->SetTexture("background.tga");	GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
	GameObjBackGround->AddComponent(go);
	scene.Add(GameObjBackGround);

	auto GameObjLogo = std::make_shared<dae::GameObject>();
	auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
	go2->SetTexture("logo.tga");
	GameObjLogo->SetRelativePosition(glm::vec3{ 216, 180 ,0 });
	GameObjLogo->AddComponent(go2);
	scene.Add(GameObjLogo);

	auto textObj = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font, textObj.get());
	textObj->SetRelativePosition(glm::vec3{ 80, 20, 0 });
	textObj->AddComponent(to);
	scene.Add(textObj);


	auto GameObjFps = std::make_shared<dae::GameObject>();
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
	GameObjFps->SetRelativePosition(glm::vec3{ 0, 0 ,0 });
	GameObjFps->AddComponent(fpsCounter);
	scene.Add(GameObjFps);

	//ControllerInit(scene, GameObjBackGround.get());

	//Children
	GameObjBackGround->AddChild(GameObjLogo.get());
	GameObjBackGround->AddChild(GameObjFps.get());
	GameObjBackGround->AddChild(textObj.get());
	

}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}