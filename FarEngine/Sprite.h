#pragma once

#include <cstddef>

#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);

	void draw();

private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	GLuint m_vboid;
};
