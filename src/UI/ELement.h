#pragma once
#include <iostream>
#include <format>
#include <raylib.h>
#include <functional>

class Element
{
	Vector2 m_postiion = {};
public:
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual ~Element() = default;
};

class Button :
	public Element
{
private:
	std::string m_text;
	Vector2 m_position = {};
	int m_size = 0;
	Rectangle m_rectangle = {};
	Sound fx_hover = LoadSound("./src/Assets/Sounds/hoverButton.wav");
	Sound fx_click = LoadSound("./src/Assets/Sounds/hoverButton.wav");

	bool hovered = false;
public:
	Button(std::string text, Vector2 position, int size)
		: m_text(text), m_position(position), m_size(size) {
		SetSoundPitch(fx_hover, 5);
		SetSoundVolume(fx_hover, 0.5);

		SetSoundPitch(fx_click, 0.5);
		SetSoundVolume(fx_click, 0.1);
	};
	void Render();
	void Update(float dt);
	bool OnHover(Rectangle bBox);
	void OnClick(std::function<void()> callback);

	~Button()
	{
		UnloadSound(fx_hover);
		UnloadSound(fx_click);
	}
};