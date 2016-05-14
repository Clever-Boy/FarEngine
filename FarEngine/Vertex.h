#pragma once

#include <GL\glew.h>

#include "Vector2.h"

struct Vertex {
	Vector2f position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
};