#include "ScreenManager.h"

#include <glm/vec2.hpp>

#include "BalloonPrefab.h"
#include "CommandsBomberMan.h"
#include "FPSCounterComponent.h"
#include "InputManager.h"
#include "PlayerBomberManPrefab.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "TextureComponent.h"

namespace dae
{

	void dae::ScreenManager::CreateMenuScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Main");

		auto GameObjBackGround = std::make_shared<dae::GameObject>();
		auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
		go->SetTexture("background.png");
		GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
		GameObjBackGround->AddComponent(go);
		scene.Add(GameObjBackGround);

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto GameType = std::make_shared<GameObject>();
		auto GameTypeText = std::make_shared<TextComponent>("GameMode:", font, GameType.get());
		GameType->SetRelativePosition(m_Width/2 - 100, 90);
		GameType->AddComponent(GameTypeText);
		scene.Add(GameType);

		auto GameModeDisplay = std::make_shared<GameObject>();
		m_pGameModeDisplayText = std::make_shared<TextComponent>("GameMode:", font, GameModeDisplay.get());
		GameModeDisplay->SetRelativePosition(m_Width / 2 - 100, 140);
		GameModeDisplay->AddComponent(m_pGameModeDisplayText);
		scene.Add(GameModeDisplay);
		
		BMCommands::BMPSwitchGame* Switch = new BMCommands::BMPSwitchGame(GameObjBackGround, this);

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, Switch);

		
	}

	void dae::ScreenManager::CreateSinglePlayerScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");

		{
			auto GameObjBackGround = std::make_shared<dae::GameObject>();
			auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
			go->SetTexture("background.png");
			GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
			GameObjBackGround->AddComponent(go);
			scene.Add(GameObjBackGround);

			auto GameObjLogo = std::make_shared<dae::GameObject>();
			auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
			go2->SetTexture("logo.tga");
			GameObjLogo->SetRelativePosition(glm::vec3{ 216, 420, 0 });
			GameObjLogo->AddComponent(go2);
			scene.Add(GameObjLogo);

			auto textObj = std::make_shared<dae::GameObject>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			auto to = std::make_shared<dae::TextComponent>("Programming 4 Exam", font, textObj.get());
			textObj->SetRelativePosition(glm::vec3{ 100, 20, 0 });
			textObj->AddComponent(to);
			scene.Add(textObj);

			auto GameObjFps = std::make_shared<dae::GameObject>();
			auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
			auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
			GameObjFps->SetRelativePosition(glm::vec3{ 0, 0, 0 });
			GameObjFps->AddComponent(fpsCounter);
			scene.Add(GameObjFps);
		}

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level.txt");
		//Level->AddRandomBreakableBlocks(scene);

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		scene.Add(GameObjBomb);

		auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb);

		auto Balloon = std::make_shared<dae::BalloonPrefab>(scene, *Level, glm::vec2{500, 250});

		//dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystemEffects>());
		//dae::servicelocator::get_sound_system().Load(0, "MainScreen.wav");
		//dae::servicelocator::get_sound_system().playMusic(0, 1.f);
	}

	void dae::ScreenManager::CreateCoopScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

		{
			auto GameObjBackGround = std::make_shared<dae::GameObject>();
			auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
			go->SetTexture("background.png");
			GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
			GameObjBackGround->AddComponent(go);
			scene.Add(GameObjBackGround);

			auto GameObjLogo = std::make_shared<dae::GameObject>();
			auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
			go2->SetTexture("logo.tga");
			GameObjLogo->SetRelativePosition(glm::vec3{ 216, 420, 0 });
			GameObjLogo->AddComponent(go2);
			scene.Add(GameObjLogo);

			auto textObj = std::make_shared<dae::GameObject>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			auto to = std::make_shared<dae::TextComponent>("Programming 4 Exam", font, textObj.get());
			textObj->SetRelativePosition(glm::vec3{ 100, 20, 0 });
			textObj->AddComponent(to);
			scene.Add(textObj);

			auto GameObjFps = std::make_shared<dae::GameObject>();
			auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
			auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
			GameObjFps->SetRelativePosition(glm::vec3{ 0, 0, 0 });
			GameObjFps->AddComponent(fpsCounter);
			scene.Add(GameObjFps);
		}

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level_01.txt");
		//Level->AddRandomBreakableBlocks(scene);

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		scene.Add(GameObjBomb);

		auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb);

		auto Balloon = std::make_shared<dae::BalloonPrefab>(scene, *Level, glm::vec2{500, 250});

		//dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystemEffects>());
		//dae::servicelocator::get_sound_system().Load(0, "MainScreen.wav");
		//dae::servicelocator::get_sound_system().playMusic(0, 1.f);
	}

	void dae::ScreenManager::CreateVersusScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");

		{
			auto GameObjBackGround = std::make_shared<dae::GameObject>();
			auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
			go->SetTexture("background.png");
			GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
			GameObjBackGround->AddComponent(go);
			scene.Add(GameObjBackGround);

			auto GameObjLogo = std::make_shared<dae::GameObject>();
			auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
			go2->SetTexture("logo.tga");
			GameObjLogo->SetRelativePosition(glm::vec3{ 216, 420, 0 });
			GameObjLogo->AddComponent(go2);
			scene.Add(GameObjLogo);

			auto textObj = std::make_shared<dae::GameObject>();
			auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			auto to = std::make_shared<dae::TextComponent>("Programming 4 Exam", font, textObj.get());
			textObj->SetRelativePosition(glm::vec3{ 100, 20, 0 });
			textObj->AddComponent(to);
			scene.Add(textObj);

			auto GameObjFps = std::make_shared<dae::GameObject>();
			auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
			auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
			GameObjFps->SetRelativePosition(glm::vec3{ 0, 0, 0 });
			GameObjFps->AddComponent(fpsCounter);
			scene.Add(GameObjFps);
		}

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level_02.txt");
		//Level->AddRandomBreakableBlocks(scene);

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		scene.Add(GameObjBomb);

		auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb);

		auto Balloon = std::make_shared<dae::BalloonPrefab>(scene, *Level, glm::vec2{500, 250});
	}

	void ScreenManager::SwitchScreens()
	{
		std::cout << "test\n";

		switch (m_CurrentScreen)
		{
		case Screen::SingleScreen:
			std::cout << "Coop\n";
			m_CurrentScreen = Screen::CoopScreen;
			m_pGameModeDisplayText->SetText("Coop");
			break;

		case Screen::CoopScreen:
			std::cout << "Versus\n";
			m_CurrentScreen = Screen::VersusScreen;
			m_pGameModeDisplayText->SetText("Versus");
			break;

		case Screen::VersusScreen:
			std::cout << "Single\n";
			m_CurrentScreen = Screen::SingleScreen;
			m_pGameModeDisplayText->SetText("Single");
			break;
		}
	}



}
