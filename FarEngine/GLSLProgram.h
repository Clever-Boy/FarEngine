#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <GL/glew.h>

#include "Error.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderfilePath, const std::string& fragmentShaderfilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();

private:
	void compileShader(const std::string& filePath, GLint shaderType);
	
	int m_numAttributes = 0;

	GLint m_programID;
	GLint m_vertexShaderID;
	GLint m_fragmentShaderID;

};

