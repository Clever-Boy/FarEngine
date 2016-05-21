#pragma once

#include <string>

#include "GLTexture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Error.h"

class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath); // Loads an image and return a GLtexture
};

