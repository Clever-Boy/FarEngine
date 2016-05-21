#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"




Sprite::Sprite()
{
	this->m_vboid = 0;
}


Sprite::~Sprite()
{
	if (this->m_vboid != 0)
	{
		glDeleteBuffers(1, &this->m_vboid);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string texturePath)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	m_texture = ResourceManager::getTexture(texturePath);

	if (this->m_vboid == 0)	{
		glGenBuffers(1, &this->m_vboid);
	}

	// Vertex data of the sprite quad (two triangles)
	Vertex vertexData[12];

	// First Triangle;
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	// Second Triangle;
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255);
	}

	vertexData[1].setColor(255, 0, 0, 255);
	vertexData[4].setColor(0, 0, 255, 255);
	vertexData[6].setColor(0, 255, 0, 255);

			
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboid); // Bind the array buffer to the vboid of this sprite	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // Send the vertex data to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the array buffer (no longer using it)
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, this->m_texture.id);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboid);

	glEnableVertexAttribArray(0);

	// Position Attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// Color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));	

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
