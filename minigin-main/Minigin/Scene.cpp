#include "Scene.h"
#include "GameObject.h"

namespace dae
{

	unsigned int Scene::m_idCounter = 0;

	Scene::Scene(const std::string& name) : m_name(name) {}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameObject> object)
	{
		m_objects.emplace_back(std::move(object));
	}

	void Scene::Remove(std::shared_ptr<GameObject> object)
	{
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
	}

	void Scene::RemoveAll()
	{
		m_objects.clear();
	}

	void Scene::Update(float deltaTime)
	{
		for (const auto& object : m_objects)
		{
			if (!object) return;

			if(object->ReturnDeleting())
			{
				Remove(object);
				continue;
			}

			object->Update(deltaTime);

		}
	}

	void Scene::FixedUpdate(float deltaTime)
	{
		for (const auto& object : m_objects)
		{
			object->FixedUpdate(deltaTime);
		}
	}

	void Scene::Render() const
	{
		for (const auto& object : m_objects)
		{
			object->Render();
		}
	}
}
