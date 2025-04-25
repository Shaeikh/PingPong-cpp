#include <iostream>
#include "raylib.h"

struct Vec2
{
	float x;
	float y;
};

int playerScore = 0;
int enemyScore = 0;

class Ball
{
public:
	Vec2 pos;
	int radius;
	Vec2 speed;

	Ball(Vec2 pos, int radius, Vec2 speed)
		: pos(pos), radius(radius), speed(speed)
	{
	}

	void draw()
	{
		DrawCircle(pos.x, pos.y, radius, WHITE);
	}

	void update()
	{
		pos.x += speed.x;
		pos.y += speed.y;

		if (pos.y - radius <= 0)
		{
			speed.y *= -1;
		}
		else if (pos.y + radius >= GetScreenHeight())
		{
			speed.y *= -1;
		}

		if (pos.x - radius <= 0)
		{
			enemyScore++;
			speed.x *= -1;
		}
		else if (pos.x + radius >= GetScreenWidth())
		{
			playerScore++;
			speed.x *= -1;
		}

		// Clamping
		if (pos.x - radius < 0) pos.x = radius;
		else if (pos.x + radius > GetScreenWidth()) pos.x = GetScreenWidth() - radius;

		if (pos.y - radius < 0) pos.y = radius;
		else if (pos.y + radius > GetScreenHeight()) pos.y = GetScreenHeight() - radius;

	}

};

class Paddle
{
public:
	Vec2 pos;
	int speed;
	int width;
	int height;

	Paddle(Vec2 pos, int speed, int width, int height)
		: pos(pos), speed(speed), width(width), height(height)
	{
	}

	void draw()
	{
		DrawRectangle(pos.x, pos.y, width, height, WHITE);
	}

	void update()
	{
		if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)))
		{
			pos.y -= speed;
		}
		if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)))
		{
			pos.y += speed;
		}

		// Clamping
		if (pos.y < 0) pos.y = 0;
		else if (pos.y + height > GetScreenHeight()) pos.y = GetScreenHeight() - height;
	}

protected:
	

};

class EnemyPaddle : public Paddle
{
public:
	EnemyPaddle(Vec2 pos, int speed, int width, int height)
		: Paddle(pos, speed, width, height)
	{
	}

	void update(const Ball &ball)
	{
		if (ball.pos.x >= GetScreenWidth() / 2)
		{
			if (ball.pos.y > pos.y + height / 2)
			{
				pos.y += speed;
			}
			if (ball.pos.y < pos.y + height / 2)
			{
				pos.y -= speed;
			}
		}

		// Clamping
		if (pos.y < 0) pos.y = 0;
		else if (pos.y + height > GetScreenHeight()) pos.y = GetScreenHeight() - height;
	}

private:

};

int main(void)
{
	int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 600;
	bool gameRunning = false;
	bool gamePause = false;

	Sound ballSound;

	InitAudioDevice();
	ballSound = LoadSound("./sounds/ball.mp3");

	Vec2 ballPosInitial = { WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };
	int ballRadius = 25;
	Vec2 ballSpeed = { 6.0f, 6.0f };

	int paddleWidth = 10;
	int paddleHeight = 150;
	int paddleSpeed = 5;

	Vec2 playerPosInitial = { 10.0f, (WINDOW_HEIGHT * 0.5f) - (paddleHeight * 0.5f) };
	Vec2 enemyPosInitial = { WINDOW_WIDTH - paddleWidth - 10.0f, (WINDOW_HEIGHT * 0.5f) - (paddleHeight * 0.5f) };
	
	Ball ball(ballPosInitial, ballRadius, ballSpeed);
	Paddle playerPaddle(playerPosInitial, paddleSpeed, paddleWidth, paddleHeight);
	EnemyPaddle enemyPaddle(enemyPosInitial, paddleSpeed - 1, paddleWidth, paddleHeight);

	
	

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ping Pong");
	SetTargetFPS(60);
	SetExitKey(KEY_NULL); // prevent escape key from closing window


	while (!WindowShouldClose())
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		BeginDrawing();

		// Intro scene
		if (!gameRunning && !gamePause)
		{

			int playRecX = WINDOW_WIDTH / 2 - 150 / 2;
			int playRecY = 200;
			int playRecWidth = 150;
			int playRecHeight = 50;

			int quitRecX = WINDOW_WIDTH / 2 - 150 / 2;
			int quitRecY = 270;
			int quitRecWidth = 150;
			int quitRecHeight = 50;

			ClearBackground(WHITE);
			DrawText(TextFormat("Ping Pong"), WINDOW_WIDTH / 2 - MeasureText("Ping Pong", 75) / 2, 50, 75, BLACK);

			DrawRectangle(playRecX, playRecY, playRecWidth, playRecHeight, BLACK);
			DrawRectangle(quitRecX, quitRecY, quitRecWidth, quitRecHeight, BLACK);

			bool mouseCollidingPlay =
				mouseX >= playRecX &&
				mouseX <= playRecX + playRecWidth &&
				mouseY >= playRecY &&
				mouseY <= playRecY + playRecHeight;
			
			bool mouseCollidingQuit =
				mouseX >= quitRecX &&
				mouseX <= quitRecX + quitRecWidth &&
				mouseY >= quitRecY &&
				mouseY <= quitRecY + quitRecHeight;

			if (mouseCollidingPlay)
			{
				DrawRectangle(playRecX, playRecY, playRecWidth, playRecHeight, GRAY); // hovers
			}
			if (mouseCollidingPlay && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				gameRunning = true;
			}

			if (mouseCollidingQuit)
			{
				DrawRectangle(quitRecX, quitRecY, quitRecWidth, quitRecHeight, GRAY); // hover
			}
			if (mouseCollidingQuit && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				CloseWindow();
			}
			DrawText(TextFormat("PLAY"), WINDOW_WIDTH / 2 - MeasureText("PLAY", 30) / 2, 200 + 25 / 2, 30, WHITE);
			DrawText(TextFormat("QUIT"), WINDOW_WIDTH / 2 - MeasureText("QUIT", 30) / 2, 270 + 25 / 2, 30, WHITE);
		}

		// Main game
		if (gameRunning && !gamePause) {
			int ballTop = ball.pos.y - ballRadius;
			int ballBot = ball.pos.y + ballRadius;
			int ballLeft = ball.pos.x - ballRadius;
			int ballRight = ball.pos.x + ballRadius;

			int playerTop = playerPaddle.pos.y;
			int playerBot = playerPaddle.pos.y + paddleHeight;
			int playerLeft = playerPaddle.pos.x;
			int playerRight = playerPaddle.pos.x + paddleWidth;

			int enemyTop = enemyPaddle.pos.y;
			int enemyBot = enemyPaddle.pos.y + paddleHeight;
			int enemyLeft = enemyPaddle.pos.x;
			int enemyRight = enemyPaddle.pos.x + paddleWidth;

			bool isCollidingPlayer = 
				ballLeft < playerRight && 
				ballRight > playerLeft && 
				ballTop < playerBot && 
				ballBot > playerTop;

			bool isCollidingEnemy =
				ballLeft < enemyRight &&
				ballRight > enemyLeft &&
				ballTop < enemyBot &&
				ballBot > enemyTop;
		
			ball.update();
			playerPaddle.update();
			enemyPaddle.update(ball);

			if (isCollidingPlayer)
			{
				PlaySound(ballSound);
				ball.speed.x *= -1;
				ball.pos.x = playerPaddle.pos.x + paddleWidth + ball.radius;
			}
			else if (isCollidingEnemy)
			{
				PlaySound(ballSound);
				ball.speed.x *= -1;
				ball.pos.x = enemyPaddle.pos.x - ball.radius;
			}
		

			BeginDrawing();
			ClearBackground(BLACK);
			ball.draw();
			playerPaddle.draw();
			enemyPaddle.draw();

			DrawText(TextFormat("%d", playerScore), 300, WINDOW_HEIGHT / 2 - 50, 100, WHITE);
			DrawText(TextFormat("%d", enemyScore), WINDOW_WIDTH - 300 - 75, WINDOW_HEIGHT / 2 - 50, 100, WHITE);

			DrawLineEx({ WINDOW_WIDTH * 0.5f, 0.0f }, { WINDOW_WIDTH * 0.5f, static_cast<float>(WINDOW_HEIGHT) }, 1, WHITE);
			DrawCircleLines(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f, 100, WHITE);
		
			// Game Pause
			if (IsKeyPressed(KEY_ESCAPE))
			{
				gamePause = true;
				gameRunning = false;
				std::cout << "Pressed";
			}
		}
		if (gamePause && !gameRunning)
		{
			int resumeRecX = WINDOW_WIDTH / 2 - 170 / 2;
			int resumeRecY = 200;
			int resumeRecWidth = 170;
			int resumeRecHeight = 50;

			int menuRecX = WINDOW_WIDTH / 2 - 200 / 2;
			int menuRecY = 270;
			int menuRecWidth = 200;
			int menuRecHeight = 50;

			ClearBackground(WHITE);
			DrawText(TextFormat("Paused"), WINDOW_WIDTH / 2 - MeasureText("Paused", 75) / 2, 50, 75, BLACK);

			DrawRectangle(resumeRecX, resumeRecY, resumeRecWidth, resumeRecHeight, BLACK);
			DrawRectangle(menuRecX, menuRecY, menuRecWidth, menuRecHeight, BLACK);

			bool mouseCollidingResume =
				mouseX >= resumeRecX &&
				mouseX <= resumeRecX + resumeRecWidth &&
				mouseY >= resumeRecY &&
				mouseY <= resumeRecY + resumeRecHeight;

			bool mouseCollidingMenu =
				mouseX >= menuRecX &&
				mouseX <= menuRecX + menuRecWidth &&
				mouseY >= menuRecY &&
				mouseY <= menuRecY + menuRecHeight;

			if (mouseCollidingResume)
			{
				DrawRectangle(resumeRecX, resumeRecY, resumeRecWidth, resumeRecHeight, GRAY); // hovers
			}
			if ((mouseCollidingResume && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
			{
				gameRunning = true;
				gamePause = false;
			}

			if (mouseCollidingMenu)
			{
				DrawRectangle(menuRecX, menuRecY, menuRecWidth, menuRecHeight, GRAY); // hover
			}
			if (mouseCollidingMenu && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				// Resetting positions
				ball.pos = ballPosInitial;
				playerPaddle.pos = playerPosInitial;
				enemyPaddle.pos = enemyPosInitial;
				gameRunning = false;
				gamePause = false;
			}
			DrawText(TextFormat("RESUME"), WINDOW_WIDTH / 2 - MeasureText("RESUME", 30) / 2, 200 + 25 / 2, 30, WHITE);
			DrawText(TextFormat("MAIN MENU"), WINDOW_WIDTH / 2 - MeasureText("MAIN MENU", 30) / 2, 270 + 25 / 2, 30, WHITE);
		}

		EndDrawing();
	}

	UnloadSound(ballSound);
	CloseAudioDevice();

	CloseWindow();

	return 0;
}