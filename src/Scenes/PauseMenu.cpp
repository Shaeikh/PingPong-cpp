#include "./Scenes.h"

PauseMenu::PauseMenu()
{
	Image i_logo = LoadImage("./src/Assets/Textures/t_pauseLogo.png");
	ImageResize(&i_logo, 800, 400);
	t_logo = LoadTextureFromImage(i_logo);
	UnloadImage(i_logo);
	fx_bg = LoadSound("./src/Assets/Sounds/bg.wav");
	SetSoundVolume(fx_bg, 0.05);
	SetSoundPitch(fx_bg, 0.8);

	PlaySound(fx_bg);
}

void PauseMenu::Render()
{

	DrawTexture(t_logo, GetScreenWidth() / 2.0f - t_logo.width / 2.0f, -50.0f, WHITE);
	b_resume.Render();
	b_main_menu.Render();
	b_quit.Render();
}

void PauseMenu::Update(float dt)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		gamePaused = false;
		Game.PopScene();
	}

	b_resume.Update(dt);
	b_resume.OnClick([]() {
		gamePaused = false;
		Game.PopScene();
	});
	
	b_main_menu.Update(dt);
	b_main_menu.OnClick([]() {
		gameStart = false, gamePaused = false;
		scorePlayer1 = 0, scorePlayer2 = 0;
		Game.ClearStack();
		Game.ChangeScene(std::make_unique<MainMenu>());
	});

	b_quit.Update(dt);
	b_quit.OnClick([]() {
		Game.ClearStack();
		CloseWindow();
	});

	
}

PauseMenu::~PauseMenu()
{
	UnloadSound(fx_bg);
	UnloadTexture(t_logo);
}