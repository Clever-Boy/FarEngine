#include "GLSLProgram.h"



GLSLProgram::GLSLProgram() : m_programID(0), m_fragmentShaderID(0), m_vertexShaderID(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string & vertexShaderfilePath, const std::string & fragmentShaderfilePath)
{
	m_programID = glCreateProgram();
	
	// Create both shader into GLint ID
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertexShaderfilePath, m_vertexShaderID);
	compileShader(fragmentShaderfilePath, m_fragmentShaderID);

	glLinkProgram(m_programID);
}

void GLSLProgram::linkShaders()
{
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	glLinkProgram(m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(m_programID);
		//Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		fatalError("Cannot Link GLSL Program");
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const std::string & uniformName)
{
	GLuint location = glGetUniformLocation(m_programID, uniformName.c_str());

	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform Location of " + uniformName + " not found");
	}

	return location;	
}

void GLSLProgram::use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string & filePath, GLint shaderID)
{
	// Open the source file of the Shader into ifstream
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Cannot open shader file" + filePath);
	}

	std::string fileContent;	// Content of the file pointed by ifstream
	std::string line;			// Line currently read of the ifstream

	while (std::getline(vertexFile, line))
	{
		fileContent += line + "\n";	// We stock each line to fileContent
	}

	vertexFile.close();	// close the ifstream

	const char* tmp = fileContent.c_str();
	glShaderSource(shaderID, 1, &tmp, nullptr);

	glCompileShader(shaderID);

	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shaderID); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader failed to compile");
	}

	// Shader compilation is successful.
}
