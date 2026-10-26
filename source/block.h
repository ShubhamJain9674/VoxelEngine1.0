#pragma once

#include "utility.h"


// testing
#include "shader.h"
#include "memory.h"
#include "texture.h"


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


	float _vertices[40] = {
	//   x      y      z      u       v
		-0.5f, -0.5f,  0.0f,  0.0f,  1.0f, 
		 0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f,  1.0f,  1.0f,  1.0f, 
		 0.5f, -0.5f,  1.0f,  0.0f,  1.0f, 
		-0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  1.0f,  0.0f,  0.0f
	};

	unsigned int _indices[36] =
	{
		0 , 2, 1,   1, 2, 3,   //front face
		4 , 5, 6,   5, 7, 6,   // middle left
		0 , 4, 2,   2, 4, 6,   // back face
		1 , 3, 5,   3, 7, 5,   // middle right
		2 , 6, 3,   3, 6, 7,   // top face
		0 , 1, 4,   1, 5, 4    // bottom face.
	};

	
};


enum class BlockType : uint8_t
{
	GRASS,
	COUNT
};

struct Block
{
	BlockType type;
	// other attrib
};


class BlockDataManager
{
public:
	BlockDataManager();
	~BlockDataManager();

	void DrawBlock(RenderData& renderData,BlockType type, glm::vec3 pos);

	const BlockTexture& GetTextures(BlockType type);

private:
	BlockTexture _textures[static_cast<size_t>(BlockType::COUNT)];


	std::unique_ptr<Voxel> _voxel{ nullptr };
	std::unique_ptr<Shader> _shader{ nullptr };

};
