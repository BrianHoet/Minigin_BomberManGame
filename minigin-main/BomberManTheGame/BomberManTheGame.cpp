#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#pragma once
#include "Minigin.h"
#include <SDL.h>
#include "SoundSystemEffects.h"
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
#include "InputManager.h"
#include "UIComponent.h"
#include "Observer.h"
#include "PlayerBomberManPrefab.h"
#include "Prefabs.h"
#include "ServiceLocator.h"


void ControllerInit(dae::Scene& scene, glm::vec2 playerstartingPos)
{
	//const float speed{ 100.f };
	//Player 1
	{
		
		

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(playerstartingPos);
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		scene.Add(GameObjBomb);
		
		//auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBomberManTex.get(), 3);
		//GameObjBomberManTex->AddComponent(pHealth);
		//
		//auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBomberManTex.get(), 0);
		//GameObjBomberManTex->AddComponent(pPoints);
		//
		//dae::HealthCommand* dieCommand = new dae::HealthCommand{ GameObjBomberManTex.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
		//dae::PointCommand* pointCommand = new dae::PointCommand{ GameObjBomberManTex.get() };
		//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);
		//
		//auto pUIObserver = std::make_shared<dae::UI>();
		//GameObjBomberManTex->MakeObserver(pUIObserver);
		
		//scene.Add(GameObjBomberManTex);
		//
		//scene.Add(GameObjBomberManTex);
		//
		////Lives Display
		//auto BomberManLivesObj = std::make_shared<dae::GameObject>("BomberMan");
		//auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		//auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		//	"Lives", BomberManLivesObj.get());
		//BomberManLivesObj->SetRelativePosition({ 5, 310, 0 });
		//BomberManLivesObj->AddComponent(textBomberManLives);
		////parent->AddChild(BomberManLivesObj.get());
		//scene.Add(BomberManLivesObj);
		//
		////Points Display
		//auto BomberManPointsObj = std::make_shared<dae::GameObject>("BomberMan");
		//auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		//	"Points", BomberManPointsObj.get());
		//BomberManPointsObj->SetRelativePosition({ 5, 330, 0 });
		//BomberManPointsObj->AddComponent(textBluePoints);
		////parent->AddChild(BomberManPointsObj.get());
		//scene.Add(BomberManPointsObj);
		
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

		dae::MoveCommand* moveCommandUpBallon = new dae::MoveCommand{ GameObjBallonTex.get(), upBallon };
		dae::MoveCommand* moveCommandDownBallon = new dae::MoveCommand{ GameObjBallonTex.get(), downBallon };
		dae::MoveCommand* moveCommandLeftBallon = new dae::MoveCommand{ GameObjBallonTex.get(), leftBallon };
		dae::MoveCommand* moveCommandRightBallon = new dae::MoveCommand{ GameObjBallonTex.get(), rightBallon };

		int controller1Index{ 0 };
		dae::InputManager::GetInstance().AddController(controller1Index);

		dae::Controller::ControllerButton controllerButton{};

		controllerButton = dae::Controller::ControllerButton::DpadUp;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUpBallon);
		controllerButton = dae::Controller::ControllerButton::DpadDown;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDownBallon);
		controllerButton = dae::Controller::ControllerButton::DpadLeft;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeftBallon);
		controllerButton = dae::Controller::ControllerButton::DpadRight;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRightBallon);
		scene.Add(GameObjBallonTex);

		auto pHealth = std::make_shared<dae::HealthComponent>(GameObjBallonTex.get(), 1);
		GameObjBallonTex->AddComponent(pHealth);
		
		auto pPoints = std::make_shared<dae::PointsComponent>(GameObjBallonTex.get(), 0);
		GameObjBallonTex->AddComponent(pPoints);

		dae::HealthCommand* dieCommandRed = new dae::HealthCommand{ GameObjBallonTex.get() };
		controllerButton = dae::Controller::ControllerButton::ButtonY;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, dieCommandRed);
		dae::PointCommand* pointCommandRed = new dae::PointCommand{ GameObjBallonTex.get() };
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, pointCommandRed);
		
		auto pUIObserver = std::make_shared<dae::UI>();
		GameObjBallonTex->MakeObserver(pUIObserver);

		parent->AddChild(GameObjBallonTex.get());

		//Lives Display
		auto BallonLivesObj = std::make_shared<dae::GameObject>("Ballon");
		auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
			"Lives", BallonLivesObj.get());
		BallonLivesObj->SetRelativePosition({ 5, 410, 0 });
		BallonLivesObj->AddComponent(textBomberManLives);
		parent->AddChild(BallonLivesObj.get());
		scene.Add(BallonLivesObj);
		
		//Points Display
		auto BallonPointsObj = std::make_shared<dae::GameObject>("Ballon");
		auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
			"Points", BallonPointsObj.get());
		BallonPointsObj->SetRelativePosition({ 5, 430, 0 });
		BallonPointsObj->AddComponent(textBluePoints);
		parent->AddChild(BallonPointsObj.get());
		scene.Add(BallonPointsObj);

		//GameObjBallonTex->NotifyObservers(dae::Update);
	}
	*/
}

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
	go->SetTexture("background.png");
	GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
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
	auto to = std::make_shared<dae::TextComponent>("Programming 4 Exam", font, textObj.get());
	textObj->SetRelativePosition(glm::vec3{ 80, 20, 0 });
	textObj->AddComponent(to);
	scene.Add(textObj);

	auto GameObjFps = std::make_shared<dae::GameObject>();
	auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
	GameObjFps->SetRelativePosition(glm::vec3{ 0, 0 ,0 });
	GameObjFps->AddComponent(fpsCounter);
	scene.Add(GameObjFps);
	
	//SoundSystemLocator::initialize();
	//std::shared_ptr<Audio> audio = std::make_shared<Audio>();
	//SoundSystemLocator::provide(audio);

	//SoundSystemLocator::getAudio().addSound("BombermanSFX(4).wav");

	//dae::CreateLevel();

	//scene.Add(dae::CreateLevel());

	/*
	auto LevelObj = std::make_shared<dae::GameObject>();

	constexpr int width{ 640 };
	constexpr int height{ 480 };

	std::vector<int> mapVector = dae::ResourceManager::GetInstance().ParseMapTxt("../Data/level.txt");

	constexpr glm::vec2 startPos{ (width / 2) - ((33.f / 2.f) * 16), (height / 2) - ((13.f / 2.f) * 16) };
	glm::vec2 pos{ startPos };

	for (size_t i{}; i < mapVector.size(); ++i)
	{
		auto pBlock = std::make_shared<dae::GameObject>();
		auto pTexture = std::make_shared<dae::TextureComponent>(pBlock.get());
		// LevelObj->AddChild(pBlock.get());
		pBlock->AddComponent(pTexture);
		pBlock->SetRelativePosition({ pos.x, pos.y });

		LevelObj->AddChild(pBlock.get());

		pTexture->SetTexture("Path.png");

		const glm::vec2 size{ pTexture->GetSize() };

		switch (mapVector[i])
		{
		case 0:
			pTexture->SetTexture("UnbreakableWall.png");
			LevelObj->AddChild(pBlock.get());
			//pBlock->SetTag("Wall");

			break;
		case 1:
			pTexture->SetTexture("Path.png");
			break;
		case 2:
			pTexture->SetTexture("Spawn.png");
			//m_SpawnPos.push_back(glm::vec2{ pos.x, pos.y });
			break;
		case 3:
			//pTexture->SetTexture("Resources/Level/teleport.png");
			//pBlock->SetTag("Teleport");
			//m_pTeleport.push_back(pBlock.get());
			break;
		default:
			LevelObj->AddChild(pBlock.get());
			break;
		}
		//m_pLevelGameObjects.push_back(std::move(pBlock));

		pos.x += size.x;

		if ((i + 1) % 33 == 0)
		{
			std::cout << '\n';
			pos.x = startPos.x;
			pos.y += size.y;
		}
	}

	scene.Add(LevelObj);
	*/

	//auto pos = levelObject->Getspawnpoints()[0];

	auto Bomberman = std::make_shared<PlayerBomberManPrefab>( scene, glm::vec2{0,0});
	
	
	dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystemEffects>());
	dae::servicelocator::get_sound_system().Load(0, "BombermanSFX(4.wav");
	dae::servicelocator::get_sound_system().play(0, 5.f);
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}