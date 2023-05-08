#include "TextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace dae
{

	TextureComponent::TextureComponent(GameObject* owner)
	{
		m_pOwner = owner;
	}

	void TextureComponent::Update(float)
	{
	}

	void TextureComponent::Render() const
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_pOwner->GetWorldPosition().x, m_pOwner->GetWorldPosition().y);
	}

	void TextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}