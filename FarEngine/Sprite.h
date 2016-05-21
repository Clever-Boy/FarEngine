#pragma once

#include <cstddef>
#include <string>

#include <GL/glew.h>

#include "GLTexture.h"


class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);

	void draw();

private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	GLuint m_vboid;
	GLTexture m_texture;
};

