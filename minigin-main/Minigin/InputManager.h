#pragma once
#include "Singleton.h"
#include "Controller.h"
#include "Commands.h"
#include <iostream>

#include <memory>
#include <map>
#include <vector>

namespace dae
{
    class GameObject;

    class InputManager final : public Singleton<InputManager>
    {
    public:
        bool ProcessInput(float deltaTime);
        void AddController(unsigned int id);
        void BindControllerToCommand(unsigned int controllerId, Controller::ControllerButton& button, Command* command);
        void BindKeyToCommand(const Uint8 &key, Command* command);
        void UpdateControllers();
        

    private:
        //Controller
        using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
        using CommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;

        CommandsMap m_Commands{};
        std::vector<std::unique_ptr<Controller>> m_Controllers{};

        //Keyboard
        using KeyboardCommands = std::map<Uint8, std::unique_ptr<Command>>;
        KeyboardCommands m_KeyCommands;


        void ProcessControllerInput(float deltaTime);
        void ProcessKeyboardInput(float deltaTime);

        
    };

}