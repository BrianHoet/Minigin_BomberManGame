#include "ScreenManager.h"

#include <glm/vec2.hpp>

#include "BalloonPrefab.h"
#include "CommandsBomberMan.h"
#include "FPSCounterComponent.h"
#include "InputManager.h"
#include "PlayerBalloomPrefab.h"
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

		m_pGameModeDisplay = std::make_shared<GameObject>();
		m_pGameModeDisplayText = std::make_shared<TextComponent>("Single", font, m_pGameModeDisplay.get());
		m_pGameModeDisplay->AddComponent(m_pGameModeDisplayText);
		m_pGameModeDisplay->SetRelativePosition(m_Width / 2 - 100, 140);

		scene.Add(m_pGameModeDisplay);
		
		std::shared_ptr<BMCommands::BMPSwitchGame> Switch = std::make_shared<BMCommands::BMPSwitchGame>(GameObjBackGround, m_pGameModeDisplay.get(), m_CurrentScreen, this);
		std::shared_ptr<BMCommands::AcceptGameMode> Accept = std::make_shared<BMCommands::AcceptGameMode>(GameObjBackGround, this);

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, Switch);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_E, Accept);


		dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystem>());
		dae::servicelocator::get_sound_system().Load(0, "BombermanSFX(4).wav");
		dae::servicelocator::get_sound_system().Load(1, "Bomberman SFX (6).wav");
		
	}

	void dae::ScreenManager::CreateSinglePlayerScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");

		
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
		

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level.txt");
		Level->AddRandomBreakableBlocks(scene);

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		auto collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBomb.get());
		GameObjBomb->AddComponent(collider);
		scene.Add(GameObjBomb);

		auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb, GameObjBackGround, true);

		auto Balloon = std::make_shared<dae::BalloonPrefab>(scene, *Level, glm::vec2{500, 250});

	}

	void dae::ScreenManager::CreateCoopScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

		
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

		

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level_01.txt");
		Level->AddRandomBreakableBlocks(scene);

		{
			//Bomb
			auto GameObjBomb = std::make_shared<dae::GameObject>();
			GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
			auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
			TextureBomb->SetTexture("Bomb_01.png");
			GameObjBomb->AddComponent(TextureBomb);
			auto Colliderbomb = std::make_shared<dae::CollisionBoxComponent>(GameObjBomb.get());
			GameObjBomb->AddComponent(Colliderbomb);
			scene.Add(GameObjBomb);

			auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb, GameObjBackGround, false);

			//Bomb2
			auto GameObjBomb2 = std::make_shared<dae::GameObject>();
			GameObjBomb2->SetRelativePosition(glm::vec2{-10, -10});
			auto TextureBomb2 = std::make_shared<dae::TextureComponent>(GameObjBomb2.get());
			TextureBomb2->SetTexture("Bomb_01.png");
			GameObjBomb2->AddComponent(TextureBomb2);
			auto Colliderbomb2 = std::make_shared<dae::CollisionBoxComponent>(GameObjBomb2.get());
			GameObjBomb2->AddComponent(Colliderbomb2);
			scene.Add(GameObjBomb2);

			auto Balloom = std::make_shared<dae::PlayerBalloomPrefab>(scene, Level->GetSpawnPosition()[1], GameObjBackGround,GameObjBomb2);
		}

		auto Balloon = std::make_shared<dae::BalloonPrefab>(scene, *Level, glm::vec2{500, 250});

		//dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystem>());
		//dae::servicelocator::get_sound_system().Load(0, "MainScreen.wav");
		//dae::servicelocator::get_sound_system().playMusic(0, 5.f);
	}

	void dae::ScreenManager::CreateVersusScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");

		
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
		

		//Level
		auto Level = std::make_shared<dae::LevelPrefab>(scene, "level_02.txt");
		Level->AddRandomBreakableBlocks(scene);

		//Bomb
		auto GameObjBomb = std::make_shared<dae::GameObject>();
		GameObjBomb->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb = std::make_shared<dae::TextureComponent>(GameObjBomb.get());
		TextureBomb->SetTexture("Bomb_01.png");
		GameObjBomb->AddComponent(TextureBomb);
		auto collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBomb.get());
		GameObjBomb->AddComponent(collider);
		scene.Add(GameObjBomb);

		auto Bomberman = std::make_shared<dae::PlayerBomberManPrefab>(scene, Level->GetSpawnPosition()[0], GameObjBomb, GameObjBackGround, false);

		//Bomb2
		auto GameObjBomb2 = std::make_shared<dae::GameObject>();
		GameObjBomb2->SetRelativePosition(glm::vec2{-10, -10});
		auto TextureBomb2 = std::make_shared<dae::TextureComponent>(GameObjBomb2.get());
		TextureBomb2->SetTexture("Bomb_01.png");
		GameObjBomb2->AddComponent(TextureBomb2);
		auto collider2 = std::make_shared<dae::CollisionBoxComponent>(GameObjBomb2.get());
		GameObjBomb2->AddComponent(collider2);
		scene.Add(GameObjBomb2);

		auto Balloom = std::make_shared<dae::PlayerBalloomPrefab>(scene, Level->GetSpawnPosition()[1], GameObjBackGround,GameObjBomb2);
	}

	void ScreenManager::CreateAppropriateScene()
	{
		dae::servicelocator::get_sound_system().playSound(1, 5.f);

		if(m_CurrentScreen == 0)
		{
			CreateSinglePlayerScreen();
		}
		else if(m_CurrentScreen == 1)
		{
			CreateCoopScreen();
		}
		else if(m_CurrentScreen == 2)
		{
			CreateVersusScreen();
		}

	}

}
