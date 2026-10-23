#pragma once

#include "utility.h"
#include <string>


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

private:

	std::string _vertexShaderSource;
	std::string _fragmentShaderSource;

	uint32_t _shaderProgram{ 0 };

};