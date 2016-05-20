#pragma once

#include <GL\glew.h>

#include "Vector2.h"

struct UV {
	float u;
	float v;
};

struct Vertex {
	Vector2f position;
	
	// UV texture coordinates
	UV uv;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};