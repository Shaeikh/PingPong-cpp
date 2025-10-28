#pragma once

#include <iostream>
#include <raylib.h>
#include <algorithm>

class Player1;
class Player2;
class Ball;

class Entity
{
protected:
	Vector2 m_position = {};
public:
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual ~Entity() = default;
};

class Ball :
	public Entity
{
private:
	float m_radius;
	Color m_color;
	Vector2 m_position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Vector2 m_velocity = { 597.69f, 565.69f };
	Sound fx_collision = {};
public:
	Ball(float radius, Color color)
		: m_radius(radius), m_color(color) {
		fx_collision = LoadSound("./src/Assets/Sounds/collision.wav");
		SetSoundVolume(fx_collision, 0.03f);
		SetSoundPitch(fx_collision, 4.0f);
	};


	void Render() override;
	void Update(float dt) override;
	void CheckCollision(const Player1& paddleLeft, const Player2& paddleRight);
	Vector2 GetPosition() const;

	~Ball()
	{
		UnloadSound(fx_collision);
	}
};

inline int scorePlayer1 = 0;
inline int scorePlayer2 = 0;

class Player1 :
	public Entity
{
protected:
	Vector2 m_size = {};
	Color m_color;
	Vector2 m_position = { 10.0f, GetScreenHeight() / 2.0f - (200.0f / 2.0f) };
	float m_velocity = 400.0f;
public:
	Player1(Vector2 size, Color color)
		: m_size(size), m_color(color) {};

	void Render() override;
	void Update(float dt) override;
	Vector4 GetBoundingBox() const {
		return { m_position.x, m_position.y, m_size.x, m_size.y };
	}

};

class Player2 :
	public Player1
{
private:
	std::string m_type; // whether player 2 is a user or ai
	float m_dt = 0.0f;
public:
	Player2(Vector2 size, Color color, std::string type)
		: Player1(size, color), m_type(type) {
		m_position.x = GetScreenWidth() - 25.0f;
	};

	void Render() override;
	void Update(float dt) override;
	void AI(Ball& ball);
};

