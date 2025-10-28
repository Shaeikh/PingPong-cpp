#include "./ELement.h"

void Button::Render()
{
	int textSize = MeasureText(m_text.c_str(), m_size);
	Vector2 tSize = MeasureTextEx(GetFontDefault(), m_text.c_str(), m_size, 0);
	//Vector2 textPos = { (GetScreenWidth() / 2.0f) - (textSize / 2.0f), (GetScreenHeight() / 2.0f) - (m_size / 2.0f) };

	Vector2 padding = { m_size * 0.5, m_size * 0.3 };

	m_rectangle = { m_position.x - padding.x, m_position.y - padding.y, textSize + padding.x * 2, m_size + padding.y * 2 };

	bool isHovering = Button::OnHover(m_rectangle);
	Rectangle bBox_hover = { m_rectangle.x, m_rectangle.y + 5, m_rectangle.width, m_rectangle.height };

	DrawRectangleRoundedLinesEx(isHovering ? bBox_hover : m_rectangle, 0.25f, 60, 3, BLACK);
	DrawRectangleRounded({ m_rectangle.x - 3, m_rectangle.y + 10, m_rectangle.width + 6, m_rectangle.height }, 0.25f, 60, BLACK);
	DrawRectangleRounded(isHovering ? bBox_hover : m_rectangle, 0.25f, 60, WHITE);
	DrawText(m_text.c_str(), m_position.x, isHovering ? m_position.y + 5 : m_position.y, m_size, BLACK);

}

bool Button::OnHover(Rectangle bBox)
{
	Vector2 m = GetMousePosition();
	return
		m.x >= bBox.x &&
		m.y >= bBox.y &&
		m.x <= bBox.x + bBox.width &&
		m.y <= bBox.y + bBox.height;
}

void Button::OnClick(std::function<void()> callback)
{
	if (Button::OnHover(m_rectangle) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		PlaySound(fx_click);
		WaitTime(0.1);
		callback();
	}
}

void Button::Update(float dt)
{
	bool wasHovered = OnHover(m_rectangle);
	if (wasHovered && !hovered) {
		PlaySound(fx_hover); // triggers only once per hover enter
	}
	hovered = wasHovered;
}

