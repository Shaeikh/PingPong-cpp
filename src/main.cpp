#include <iostream>
#include <raylib.h>
#include <format>

#include "./Scenes/Scenes.h"
#include "./UI/ELement.h"


int main(void)
{
	int baseWidth = 1200;
	int baseHeight = 800;
	InitWindow(baseWidth, baseHeight, "Ping Pong");
	InitAudioDevice();
	SetExitKey(0);
	SetTargetFPS(120);

	Game.ChangeScene(std::make_unique<MainMenu>());
	
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		
		BeginDrawing();
		ClearBackground(WHITE);

		Game.Render();
		Game.Update(dt);

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
	return 0;
}