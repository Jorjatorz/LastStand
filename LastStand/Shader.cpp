#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "FLog.h"
#include "Matrix4.h"
#include "Vector3.h"

//#define DEBUG_SHADERS

Shader::Shader(std::string name)
	:_program(0),
	_name(name)
{
}


Shader::~Shader(void)
{
	//delete the program
	glDeleteProgram(_program);
}

bool Shader::loadFromDisk(std::string filePath)
{
	std::ifstream file;
	std::stringstream strStreamBuffer; //string stream buffer

	//vertex-------------------------------------

	//load
	file.open(filePath + ".vert");

	std::string vertexShaderStr; 
	if (!file.is_open())
	{
		FLog(FLog::ERROR, "Error loading VERTEX shader: " + filePath);
		return false;
	}
	else
	{
		strStreamBuffer << file.rdbuf(); //read the file
		vertexShaderStr = strStreamBuffer.str(); //copy to a string

		file.close();
	}


	//create the vertex shader source
	const GLchar* vertexShaderSource = vertexShaderStr.c_str();

	//Create and compile the shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check vertex shader
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);


	if (status == 0)
	{
		FLog(FLog::WARNING, buffer);
	}

	//fragment------------------------

	//load
	file.open(filePath + ".frag");

	std::string fragmentShaderStr;
	if (!file.is_open())
	{
		FLog(FLog::ERROR, "Error loading FRAGMENT shader: " + filePath);
		return false;
	}
	else
	{
		//reset stream buffer
		strStreamBuffer.str("");
		strStreamBuffer.clear();

		strStreamBuffer << file.rdbuf();
		fragmentShaderStr = strStreamBuffer.str();

		file.close();
	}

	//Create the fragment shader
	const GLchar* fragmentShaderSource = fragmentShaderStr.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);

	if (status == 0)
	{
		FLog(FLog::WARNING, buffer);
	}


	// Link the vertex and fragment shader into a shader program--------------------
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Fragment shader outputs
	glBindFragDataLocation(program, 0, "outColor"); //color to the buffer number 0
	glBindFragDataLocation(program, 1, "outPosition"); //vertex position to the buffer number 1
	glBindFragDataLocation(program, 2, "outNormals"); //normal to the buffer number 2
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glLinkProgram(program);

	//we finished the link so we can delete the shader
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	//save the program
	_program = program;

	return true;
}

void Shader::bind()
{
	glUseProgram(_program);
}
void Shader::unBind()
{
	glUseProgram(0);
}

// sent texture value
void Shader::uniformTexture(const std::string& uniformName, GLint activeTextureSlot)
{
	//glActiveTexture(GL_TEXTURE0+slot);
	GLuint id = glGetUniformLocation(_program, uniformName.c_str());
	if (id == -1)
#ifdef DEBUG_SHADERS
		FLog(FLog::WARNING, _name + " Couldn't get uniform location of " + uniformName);
#endif

	glUniform1i(id, activeTextureSlot);
}

// sent int value
void Shader::uniform(const std::string& uniformName, GLint value)
{
	GLuint id = glGetUniformLocation(_program, uniformName.c_str());
	if (id == -1)
#ifdef DEBUG_SHADERS
		FLog(FLog::WARNING, _name + " Couldn't get uniform location of " + uniformName);
#endif
	glUniform1iARB(id, value);
}

// sent float value
void Shader::uniform(const std::string& uniformName, GLfloat value)
{
	GLuint id = glGetUniformLocation(_program, uniformName.c_str());
	if (id == -1)
#ifdef DEBUG_SHADERS
		FLog(FLog::WARNING, _name + " Couldn't get uniform location of " + uniformName);
#endif
	glUniform1fARB(id, value);
}

void Shader::uniform(const std::string& uniformName, const Vector3& value)
{
	GLuint id = glGetUniformLocation(_program, uniformName.c_str());
	if (id == -1)
#ifdef DEBUG_SHADERS
		FLog(FLog::WARNING, _name + " Couldn't get uniform location of " + uniformName);
#endif
	glUniform3fvARB(id, 1, value.getValuePtr());
}

void Shader::uniformMatrix(const std::string & uniformName, const Matrix4& value)
{
	GLuint id = glGetUniformLocation(_program, uniformName.c_str());
	if (id == -1)
#ifdef DEBUG_SHADERS
		FLog(FLog::WARNING, _name + " Couldn't get uniform location of " + uniformName);
#endif
	glUniformMatrix4fvARB(id, 1, false, value.getValuePtr());
}