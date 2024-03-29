#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL\glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"
#include "Error.h"
#include "GLTexture.h"
#include "ImageLoader.h"

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
	std::vector<Sprite*> m_sprites;
	GLSLProgram m_colorProgram;	
};

