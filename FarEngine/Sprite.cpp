#include "Sprite.h"

#include "Vertex.h"



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

void Sprite::init(float x, float y, float width, float height)
{
	this->m_x = x;
	this->m_y = y;
	this->m_width = width;
	this->m_height = height;

	if (this->m_vboid == 0)	{
		glGenBuffers(1, &this->m_vboid);
	}

	// Vertex data of the sprite quad (two triangles)
	Vertex vertexData[12];

	// First Triangle;
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;
	
	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	// Second Triangle;
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

			
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboid); // Bind the array buffer to the vboid of this sprite	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // Send the vertex data to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the array buffer (no longer using it)
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboid);

	glEnableVertexAttribArray(0);

	// Position Attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// Color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
