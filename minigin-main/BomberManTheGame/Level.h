#pragma once
#include <iostream>

#include "GameObject.h"

class Level: public dae::GameObject
{
public:

	Level(const std::string& file);

private:

	void LevelCreation(const std::string& file);


	std::shared_ptr<GameObject> m_Test;
	std::vector<std::shared_ptr<GameObject>> m_pLevelGameObjects;
};

