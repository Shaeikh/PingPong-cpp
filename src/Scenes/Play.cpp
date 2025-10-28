#include "./Scenes.h"

void Play::Render()
{
	/*DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), BLACK);
	DrawLine(GetScreenWidth() / 2 / 2, 0, GetScreenWidth() / 2 / 2, GetScreenHeight(), BLACK);
	DrawLine(GetScreenWidth() * 3 / 4, 0, GetScreenWidth() * 3 / 4, GetScreenHeight(), BLACK);
	DrawLine(0, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, BLACK);*/

	DrawRectangleLinesEx({ 0, 0, GetScreenWidth() + 0.0f, GetScreenHeight() + 0.0f }, 5, BLACK);

	DrawLineEx({ GetScreenWidth() / 2.0f, 0 }, { GetScreenWidth() / 2.0f, GetScreenHeight() - 0.0f }, 5, BLACK);
	//DrawCircleLinesV({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 200, BLACK);
	DrawCircleV({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 150, BLACK);
	DrawCircleV({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 145, WHITE);

	const int fontSize = 130;

	std::string txt_p1 = std::to_string(scorePlayer1);
	std::string txt_p2 = std::to_string(scorePlayer2);

	Vector2 txt_p1Size = { MeasureText(txt_p1.c_str(), fontSize), fontSize};
	Vector2 txt_p2Size = { MeasureText(txt_p2.c_str(), fontSize), fontSize};

	DrawText(txt_p1.c_str(), ((GetScreenWidth() / 2) - txt_p1Size.x) - (GetScreenWidth() / 2 / 2) + (txt_p1Size.x / 2), (GetScreenHeight() / 2) - fontSize / 2, fontSize, BLACK);
	DrawText(txt_p2.c_str(), (GetScreenWidth() / 2) + (GetScreenWidth() / 2 / 2) - (txt_p1Size.x / 2), (GetScreenHeight() / 2) - fontSize / 2, fontSize, BLACK);

	ball.Render();
	paddleLeft.Render();
	paddleRight.Render();

	DrawText("Press SPACE to Start the game", GetScreenWidth() / 2 - MeasureText("Press SPACE to Start the game", 60) / 2, GetScreenHeight() / 4 - (60 / 2), 60, gameStart ? Color{0, 0, 0, 0} : BLACK);

}

void Play::Update(float dt)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		gameStart = true;
	}
	else if (IsKeyPressed(KEY_ESCAPE))
	{
		gamePaused = !gamePaused;
		if (gamePaused)
			Game.ChangeScene(std::make_unique<PauseMenu>());
	}

	if (gameStart && !gamePaused)
	{
		ball.Update(dt);
		ball.CheckCollision(paddleLeft, paddleRight);

		paddleLeft.Update(dt);
	
		paddleRight.Update(dt);
		paddleRight.AI(ball);
	}
}