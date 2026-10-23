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