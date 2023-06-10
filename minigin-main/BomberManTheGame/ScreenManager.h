#pragma once
#include "Singleton.h"
#include "TextComponent.h"

namespace dae
{

	class ScreenManager
	{
	public:
		enum Screen
		{
			SingleScreen,
			CoopScreen,
			VersusScreen
		};

		ScreenManager() = default;
		~ScreenManager() = default;
		ScreenManager(const ScreenManager& other) = delete;
		ScreenManager(ScreenManager&& other) = delete;
		ScreenManager& operator=(const ScreenManager& other) = delete;
		ScreenManager& operator=(ScreenManager&& other) = delete;

		void CreateMenuScreen();
		void CreateSinglePlayerScreen();
		void CreateCoopScreen();
		void CreateVersusScreen();

		Screen GetCurrentEnum() const { return m_CurrentScreen; }
		void SetCurrentEnum(int enumid)
		{
			m_CurrentScreen = static_cast<Screen>(enumid);
		};

		void SwitchScreens();

	private:

		Screen m_CurrentScreen = Screen::SingleScreen;
		float m_Width{ 640 };
		float m_Height{ 480 };

		std::shared_ptr<TextComponent> m_pGameModeDisplayText;
	};

}
