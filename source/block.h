#pragma once

#include "utility.h"

enum class BlockType : uint8_t
{
	DIRT,
	GRASS
};

struct Block
{
	BlockType type;
	// position
	// other attrib
};


class Voxel
{

public:

	Voxel();
	~Voxel();

private:
	
	uint32_t _VAO;
	uint32_t _VBO;
	uint32_t _IBO;


	float _vertices[24] = {
	//   x      y      z
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f
	};

	unsigned int _indices[24] =
	{
		0 , 1, 2, 3,   //front face
		0 , 4, 2, 6,   // middle left
		4 , 5, 6, 7,   // back face
		1 , 5, 3, 7,   // middle right
		2 , 3, 6, 7,   // top face
		0 , 1, 4, 5    // bottom face.
	};

};