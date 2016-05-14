#include "MainGame.h"

MainGame::MainGame()
{
	this->m_window = nullptr;
	this->m_screenWidth = 1024;
	this->m_screenHeight = 768;
	this->m_state = GameState::PLAY;
	this->m_time = 0.0f;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	this->initSystems();

	this->initShaders();

	this->m_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	this->gameLoop();
}

void MainGame::initSystems()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
		fatalError(SDL_GetError());

	this->m_window = SDL_CreateWindow("FarEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->m_screenWidth, this->m_screenHeight, SDL_WINDOW_OPENGL);

	if (this->m_window == nullptr)
		fatalError(SDL_GetError());

	SDL_GLContext glContext = SDL_GL_CreateContext(this->m_window);
	if (glContext == nullptr)
		fatalError("ERROR : Cannot create OpenGL context from window");

	if (glewInit() > 0)
		fatalError("ERROR : Cannot init GLEW");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void MainGame::initShaders()
{
	m_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (this->m_state != GameState::EXIT)
	{
		this->m_time += 0.0001;
		this->processInput();
		this->draw();
	}
}

void MainGame::processInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			this->m_state = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << "-" << e.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.use();

	GLuint timeLocation = m_colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, m_time);

	this->m_sprite.draw();

	m_colorProgram.unuse();

	SDL_GL_SwapWindow(this->m_window);
}
