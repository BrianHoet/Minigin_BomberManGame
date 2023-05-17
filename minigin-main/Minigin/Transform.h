#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec2& GetPosition() const { return m_position; }
		void SetPosition(float x, float y);
	private:
		glm::vec2 m_position;
	};
}
