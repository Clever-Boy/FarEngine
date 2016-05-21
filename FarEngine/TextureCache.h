#pragma once

#include <map>

#include "GLTexture.h"
#include "ImageLoader.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(std::string label);

private:
	std::map<std::string, GLTexture> m_texturemap;
};

