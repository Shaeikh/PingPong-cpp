#include "Entity.h"

void Player1::Render()
{
	DrawRectangleV(m_position, m_size, m_color);
}

void Player1::Update(float dt)
{
	if (IsKeyDown(KEY_S))
	{
		m_position.y += m_velocity * dt;
	}
	else if (IsKeyDown(KEY_W))
	{
		m_position.y -= m_velocity * dt;
	}
	
	m_position.y = std::clamp(m_position.y, 10.0f, GetScreenHeight() - m_size.y - 10.0f);
}