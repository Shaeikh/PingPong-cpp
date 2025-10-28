#include "Entity.h"

void Ball::Render()
{
	DrawCircle(m_position.x, m_position.y, m_radius, m_color);
}

void Ball::Update(float dt)
{
	m_position.x += (m_velocity.x * dt);
	m_position.y += m_velocity.y * dt;
	

	if (m_position.x < m_radius)
		scorePlayer2++;
	else if (m_position.x > GetScreenWidth() - m_radius)
		scorePlayer1++;

	//std::cout << "P1 Score: " << scorePlayer1 << " P2 Score: " << scorePlayer2 << std::endl;


	// Keepin the ball within screen boundaries, inverting the direction on contact with respected x-y component
	if (m_position.x < m_radius || m_position.x > GetScreenWidth() - m_radius)
	{
		PlaySound(fx_collision);
		m_position.x = std::clamp(m_position.x, m_radius, GetScreenWidth() - m_radius);
		m_velocity.x *= -1;
	}
	else if (m_position.y - m_radius < 0 || m_position.y > GetScreenHeight() - m_radius)
	{
		PlaySound(fx_collision);
		m_position.y = std::clamp(m_position.y, m_radius, GetScreenHeight() - m_radius);
		m_velocity.y *= -1;
	}
}

// Colliding with the paddles
void Ball::CheckCollision(const Player1& paddleLeft, const Player2& paddleRight) {
	/*Vector2 pLeftPos = { paddleLeft.GetBoundingBox().x, paddleLeft.GetBoundingBox().y };
	Vector2 pLeftSize = { paddleLeft.GetBoundingBox().z, paddleLeft.GetBoundingBox().w };

	Vector2 pRightPos = { paddleRight.GetBoundingBox().x, paddleRight.GetBoundingBox().y };
	Vector2 pRightSize = { paddleRight.GetBoundingBox().z, paddleRight.GetBoundingBox().w };*/

	float p1_closestX = std::clamp(m_position.x, paddleLeft.GetBoundingBox().x, paddleLeft.GetBoundingBox().x + paddleLeft.GetBoundingBox().z);
	float p1_closestY = std::clamp(m_position.y, paddleLeft.GetBoundingBox().y, paddleLeft.GetBoundingBox().y + paddleLeft.GetBoundingBox().w);

	float p2_closestX = std::clamp(m_position.x, paddleRight.GetBoundingBox().x, paddleRight.GetBoundingBox().x + paddleRight.GetBoundingBox().z);
	float p2_closestY = std::clamp(m_position.y, paddleRight.GetBoundingBox().y, paddleRight.GetBoundingBox().y + paddleRight.GetBoundingBox().w);

	float p1_ball_distance = std::sqrt(((m_position.x - p1_closestX) * (m_position.x - p1_closestX)) + ((m_position.y - p1_closestY) * (m_position.y - p1_closestY)));
	float p2_ball_distance = std::sqrt(((m_position.x - p2_closestX) * (m_position.x - p2_closestX)) + ((m_position.y - p2_closestY) * (m_position.y - p2_closestY)));

	bool IsCollidingPaddleLeft =
		p1_ball_distance <= m_radius;

	bool IsCollidingPaddleRight =
		p2_ball_distance <= m_radius;

	if (IsCollidingPaddleLeft)
	{
		PlaySound(fx_collision);
		m_position.x = paddleLeft.GetBoundingBox().x + paddleLeft.GetBoundingBox().z + m_radius; // clamping so it won't stuck
		m_velocity.x *= -1;

	}
	else if (IsCollidingPaddleRight)
	{
		PlaySound(fx_collision);
		m_position.x = paddleRight.GetBoundingBox().x - m_radius;
		m_velocity.x *= -1;
	}
}

Vector2 Ball::GetPosition() const
{
	return m_position;
}