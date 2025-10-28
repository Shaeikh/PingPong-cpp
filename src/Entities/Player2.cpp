#include "Entity.h"

void Player2::Render()
{
	DrawRectangleV(m_position, m_size, m_color);
}

void Player2::Update(float dt)
{
	m_dt = dt;
	if (m_type == "USER")
	{
		if (IsKeyDown(KEY_DOWN))
		{
			m_position.y += m_velocity * dt;
		}
		else if (IsKeyDown(KEY_UP))
		{
			m_position.y -= m_velocity * dt;
		}
		m_position.y = std::clamp(m_position.y, 10.0f, GetScreenHeight() - m_size.y - 10.0f);
		
	}
	

	
}

void Player2::AI(Ball& ball)
{
	Vector2 ball_position = ball.GetPosition();
	if (m_type == "AI")
	{
		if (ball_position.x >= GetScreenWidth() / 2.0f)
		{
			if (ball_position.y > m_position.y)
				m_position.y += m_velocity * m_dt;
		
			else if (ball_position.y < m_position.y)
				m_position.y -= m_velocity * m_dt;
		}
		m_position.y = std::clamp(m_position.y, 10.0f, GetScreenHeight() - m_size.y - 10.0f);
	}
}