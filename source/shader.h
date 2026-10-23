#pragma once

#include "utility.h"
#include <string>

#include "GLM/glm.hpp"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

struct RenderData {

	glm::mat4 model{ glm::mat4(1.0f) };
	glm::mat4 projection{ glm::mat4(1.0f) };

};

class Shader 
{
public:
	
	/*
		vsSource: FilePath to vertexShader
		fsSource: FilePath to fragmentShader
	*/
	Shader(const char* vsSource,const char* fsSource);
	~Shader();

	void UseShader();

	void UpdateUniformData(const RenderData& data);


private:

	std::string _vertexShaderSource;
	std::string _fragmentShaderSource;

	uint32_t _shaderProgram{ 0 };

	// uniform ids.
	uint32_t _u_model_id;
	uint32_t _u_projection_id;
};