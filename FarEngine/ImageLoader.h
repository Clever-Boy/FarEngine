#pragma once

#include <string>

#include "GLTexture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Error.h"

class ImageLoader
{
public:
	GLTexture loadPNG(std::string filePath);
};

