#pragma once

#include "utility.h"


// testing
#include "shader.h"
#include "memory.h"



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


// since there will be only one type of block this class is just for encapsulation.
// only one instance of Voxel should exist.
class Voxel
{

public:

	Voxel();
	~Voxel();

	
	bool Init();
	void DrawVoxel();


private:
	
	uint32_t _VAO{0};
	uint32_t _VBO{0};
	uint32_t _IBO{0};


	float _vertices[24] = {
	//   x      y      z
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,

		-0.5f, -0.5f,  1.0f,
		 0.5f, -0.5f,  1.0f,
		-0.5f,  0.5f,  1.0f,
		 0.5f,  0.5f,  1.0f
	};

	unsigned int _indices[36] =
	{
		0 , 1, 2,   1, 3, 2,   //front face
		4 , 6, 5,   5, 6, 7,   // middle left
		0 , 2, 4,   4, 2, 6,   // back face
		1 , 5, 3,   5, 7, 3,   // middle right
		2 , 3, 6,   3, 7, 6,   // top face
		0 , 1, 4,   1, 4, 5    // bottom face.
	};

	
};