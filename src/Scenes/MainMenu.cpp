#include "./Scenes.h"

MainMenu::MainMenu()
{
	Image i_logo = LoadImage("./src/Assets/Textures/t_logo.png");
	ImageResize(&i_logo, 800, 400);
	t_logo = LoadTextureFromImage(i_logo);
	UnloadImage(i_logo);
	fx_bg = LoadSound("./src/Assets/Sounds/bg.wav");
	SetSoundVolume(fx_bg, 0.05);
	SetSoundPitch(fx_bg, 0.8);
	
	PlaySound(fx_bg);
}

void MainMenu::Render()
{
	
	DrawTexture(t_logo, GetScreenWidth() / 2.0f - t_logo.width / 2.0f, -50.0f, WHITE);
	b_1_player.Render();
	b_2_player.Render();
	b_quit.Render();
}

void MainMenu::Update(float dt)
{
	b_1_player.Update(dt);
	b_1_player.OnClick([]() {
		GAME_MODE = "AI";
		Game.SuspendScene(std::make_unique<Play>());
	});

	b_2_player.Update(dt);
	b_2_player.OnClick([]() {
		GAME_MODE = "USER";
		Game.SuspendScene(std::make_unique<Play>());
	});

	b_quit.Update(dt);
	b_quit.OnClick([]() {
		Game.ClearStack();
		CloseWindow();
	});

}

MainMenu::~MainMenu() 
{
	UnloadSound(fx_bg);
	UnloadTexture(t_logo);
}