#include <SDL.h>
#include "InputManager.h"
#include <map>

#include "ServiceLocator.h"

namespace dae
{
	class Transform;
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT) 
        {
            return false;
        }
        if (e.type == SDL_KEYDOWN) 
        {
            
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) 
        {
        }
        // etc...
    }

    ProcessKeyboardInput(deltaTime);
    ProcessControllerInput(deltaTime);

    return true;
}

//Controller
void dae::InputManager::AddController(unsigned int id)
{
    m_Controllers.emplace_back(std::make_unique<Controller>(id));
}
void dae::InputManager::BindControllerToCommand(unsigned int id, Controller::ControllerButton& button, Command* command)
{
    ControllerKey key = ControllerKey(id, button);
    m_Commands.insert({ key, std::unique_ptr<Command>(command) });
}
void dae::InputManager::UpdateControllers()
{
    for (auto& controller : m_Controllers)
    {
        controller->Update();
    }
}
void dae::InputManager::ProcessControllerInput(float deltaTime)
{
    for (auto& controller : m_Controllers)
    {
        for (auto& command : m_Commands)
        {
            const auto controllerKey = command.first.second;
            const unsigned int controllerId = command.first.first;
            if (controller->GetIDOfController() == controllerId && controller->IsPressed(static_cast<int>(controllerKey)))
            {
                command.second->Execute(deltaTime);
            }
        }
    }
}

//Keyboard
void dae::InputManager::BindKeyToCommand(const Uint8& key, Command* command)
{
    m_KeyCommands.insert({ key, std::unique_ptr<Command>(command) });
}
void dae::InputManager::ProcessKeyboardInput(float deltaTime)
{
    const Uint8* pStates = SDL_GetKeyboardState(nullptr);

    for (auto& keyCommand : m_KeyCommands)
    {
        if (pStates[keyCommand.first])
        {
            keyCommand.second->Execute(deltaTime);
        }
    }
}
