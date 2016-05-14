#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"
#include "Error.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void draw();

	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_state;
	float m_time;

	// tmp
	Sprite m_sprite;
	GLSLProgram m_colorProgram;
};

