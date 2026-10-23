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

	uint32_t shader = GLCall(glCreateShader(shaderType));

	GLCall(glShaderSource(shader, 1, &source, NULL));


	GLCall(glCompileShader(shader));

	int err;

	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &err));
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

	_shaderProgram = GLCall(glCreateProgram());

	GLCall(glAttachShader(_shaderProgram, vertexShader));
	GLCall(glAttachShader(_shaderProgram, fragmentShader));
	
	GLCall(glLinkProgram(_shaderProgram));

	int status = 0;
	GLCall(glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status));
	if (status != GL_TRUE)
	{
		char message[1024];
		glGetProgramInfoLog(_shaderProgram, 1024, NULL, message);
		std::cout << "SHADER LINK ERROR : " << message << std::endl;
		return;
	}

	GLCall(glValidateProgram(_shaderProgram));

	status = 0;

	glGetProgramiv(_shaderProgram, GL_VALIDATE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char message[1024];
		glGetProgramInfoLog(_shaderProgram, 1024, NULL, message);
		std::cout << "SHADER VALIDATE ERROR : " << message << std::endl;
		return;
	}
	
	// cleanup shaders
	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));

	// uniform ids.

	_u_model_id = GLCall(glGetUniformLocation(_shaderProgram, "u_model"));
	_u_projection_id = GLCall(glGetUniformLocation(_shaderProgram, "u_projection"));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(_shaderProgram));
}


void Shader::UseShader()
{
	GLCall(glUseProgram(_shaderProgram));
}

void Shader::UpdateUniformData(const RenderData& data)
{
	GLCall(glUniformMatrix4fv(_u_model_id, 1, GL_FALSE, glm::value_ptr(data.model)));
	GLCall(glUniformMatrix4fv(_u_projection_id, 1, GL_FALSE, glm::value_ptr(data.projection)));
}


