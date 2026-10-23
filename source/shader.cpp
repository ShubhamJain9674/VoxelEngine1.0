#include "shader.h"

#include "filehandling.h"

/*
*NOTE for me:-
* filepath is relative to where the executable is called from not relative to executable.
* to pass relative path with respect to executable, 
* need to resolve absoulte path of executable first.
*/


internal std::string GetShaderType(GLenum shaderType)
{
	switch (shaderType)
	{
		case GL_VERTEX_SHADER:
			return "VERTEX SHADER";
			break;

		case GL_FRAGMENT_SHADER:
			return "FRAGMENT SHADER";
			break;

		case GL_COMPUTE_SHADER:
			return "COMPUTER SHADER";
			break;
		case GL_TESS_CONTROL_SHADER:
			return "TESS CONTROL SHADER";
			break;
		case GL_TESS_EVALUATION_SHADER:
			return "TESS EVALUATION SHADER";
			break;
		case GL_GEOMETRY_SHADER:
			return "GEOMETRY SHADER";
			break;
		default:
			return "Invalid Shader Type!";
			break;
	}
	return "";
}

/* source path is relative to executable.*/
internal uint32_t CreateShader(const char* source,GLenum shaderType)
{

	uint32_t shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &source, NULL);


	glCompileShader(shader);

	int err;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
	if (err != GL_TRUE)
	{
		int logLength = 0;
		char message[1024];
		glGetShaderInfoLog(shader, 1024, &logLength, message);



		std::cout << "SHADER COMPILE ERROR : "
			      << "(" << GetShaderType(shaderType) << ")"
				  << message << std::endl;
		return 0;
	}
	return shader;
}


Shader::Shader(const char* vsSource, const char* fsSource)
{
	if (!FileManager::ReadShaderFile(vsSource, _vertexShaderSource))
		return;

	if (!FileManager::ReadShaderFile(fsSource, _fragmentShaderSource))
		return;

	const char* vertexShaderSource = _vertexShaderSource.c_str();
	const char* fragmentShaderSource = _fragmentShaderSource.c_str();


	uint32_t vertexShader = CreateShader(vertexShaderSource,GL_VERTEX_SHADER);
	uint32_t fragmentShader = CreateShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	_shaderProgram = glCreateProgram();

	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	
	glLinkProgram(_shaderProgram);

	int status = 0;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char message[1024];
		glGetProgramInfoLog(_shaderProgram, 1024, NULL, message);
		std::cout << "SHADER LINK ERROR : " << message << std::endl;
		return;
	}

	glValidateProgram(_shaderProgram);

	status = 0;

	glGetProgramiv(_shaderProgram, GL_VALIDATE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char message[1024];
		glGetProgramInfoLog(_shaderProgram, 1024, NULL, message);
		std::cout << "SHADER VALIDATE ERROR : " << message << std::endl;
		return;
	}



}

void Shader::UseShader()
{
	glUseProgram(_shaderProgram);
}


