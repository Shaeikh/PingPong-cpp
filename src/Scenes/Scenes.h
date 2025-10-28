#pragma once

#include <iostream>
#include <raylib.h>
#include <format>
#include <string> 

#include "./Manager.h"
#include "../Entities/Entity.h"
#include "../UI/ELement.h"

inline std::string GAME_MODE = "USER";
inline bool gameStart = false;
inline bool gamePaused = false;

class MainMenu
	: public Scene
{
private:
	Button b_1_player = Button("1 Player", { GetScreenWidth() / 2.0f - MeasureText("1 Player", 40) / 2.0f, 300}, 40); // Button b(...params) <- WRONG! C++ grammar goofy asl
	Button b_2_player = Button("2 Player", { GetScreenWidth() / 2.0f - MeasureText("2 Player", 40) / 2.0f, 400 }, 40);
	Button b_quit = Button("Exit game", { GetScreenWidth() / 2.0f - MeasureText("Exit Game", 40) / 2.0f, 500 }, 40);
	
	Texture2D t_logo = {};
	Sound fx_bg = {};
public:
	MainMenu();
	void Render() override;
	void Update(float dt) override;
	~MainMenu() override;
};

class PauseMenu
	: public Scene
{
private:
	Button b_resume = Button("Play", { GetScreenWidth() / 2.0f - MeasureText("Play", 40) / 2.0f, 300 }, 40); // Button b(...params) <- WRONG! C++ grammar goofy asl
	Button b_main_menu = Button("Menu", { GetScreenWidth() / 2.0f - MeasureText("Menu", 40) / 2.0f, 400 }, 40);
	Button b_quit = Button("Exit", { GetScreenWidth() / 2.0f - MeasureText("Exit", 40) / 2.0f, 500 }, 40);

	Texture2D t_logo = {};
	Sound fx_bg = {};
public:
	PauseMenu();
	void Render() override;
	void Update(float dt) override;
	~PauseMenu();
};

class Play
	: public Scene
{
private:
	Ball ball = Ball(35.0f, BLACK);
	Player1 paddleLeft = Player1({ 15.0f, 200.0f }, BLACK);
	Player2 paddleRight = Player2({ 15.0f, 200.0f }, BLACK, GAME_MODE);
public:
	void Render() override;
	void Update(float dt) override;
};

