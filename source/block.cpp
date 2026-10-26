#include "block.h"


Voxel::Voxel()
{

}


bool Voxel::Init()
{
	GLCall((1, &_VAO));
	GLCall(glBindVertexArray(_VAO));

	GLCall(glGenBuffers(1, &_IBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO));

	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(_indices),
		_indices,
		GL_STATIC_DRAW
	));

	GLCall(glGenBuffers(1, &_VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER,
		sizeof(_vertices),
		_vertices,
		GL_STATIC_DRAW
	));

	GLCall(glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(_vertices[0]) * 5,
		0
	));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(_vertices[0]) * 5,
		(void*)(3 * sizeof(_vertices[0]))
	));

	GLCall(glEnableVertexAttribArray(1));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	
	return true;
}


Voxel::~Voxel()
{
	GLCall(glDeleteVertexArrays(1, &_VAO));
	GLCall (glDeleteBuffers(1, &_IBO));
	GLCall(glDeleteBuffers(1, &_VBO));
}


void Voxel::DrawVoxel()
{

	GLCall(glBindVertexArray(_VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_IBO));
	GLCall(glDrawElements(GL_TRIANGLES,36, GL_UNSIGNED_INT, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	GLCall(glUseProgram(0));
}





constexpr size_t Index(BlockType type)
{
	return static_cast<size_t>(type);
}

BlockDataManager::BlockDataManager()
	:_textures{}
{
	
	// temp 
	// later write a conf file parser and define locations/filename there
	
	// or dont be lazy and learn and create an atlas map.
	_textures[Index(BlockType::GRASS)].bottom = std::make_unique<Texture>("assets/textures/dirt.png");
	_textures[Index(BlockType::GRASS)].top = std::make_unique<Texture>("assets/textures/grass_block_top.png");
	_textures[Index(BlockType::GRASS)].side = std::make_unique<Texture>("assets/textures/grass_block_side.png");


	_textures[Index(BlockType::GRASS)].bottom->Load();
	_textures[Index(BlockType::GRASS)].top->Load();
	_textures[Index(BlockType::GRASS)].side->Load();


	_voxel = std::make_unique<Voxel>();
	_voxel->Init();

	_shader = std::make_unique<Shader>("shaders/vertex.shader", "shaders/fragment.shader");

}

BlockDataManager::~BlockDataManager()
{
}

void BlockDataManager::DrawBlock(RenderData& renderData,BlockType type, glm::vec3 pos)
{
	renderData.model = glm::translate(
		renderData.model,
		pos
	);

	_shader->UseShader();

	auto& texture = GetTextures(type);
	texture.side->Use();

	_shader->UpdateUniformData(renderData);

	if (_voxel)
	{
		_voxel->DrawVoxel();
	}
}

const BlockTexture& BlockDataManager::GetTextures(BlockType type)
{

	if (type == BlockType::COUNT)
	{
		// default texture
		return _textures[0];
	}

	return _textures[Index(type)];
}

