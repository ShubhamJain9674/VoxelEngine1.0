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
		sizeof(_vertices[0]) * 3,
		0
	));

	GLCall(glEnableVertexAttribArray(0));

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


void Voxel::DrawVoxel(Shader* shader)
{
	if (!shader)
		return;

	shader->UseShader();

	GLCall(glBindVertexArray(_VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_IBO));
	GLCall(glDrawElements(GL_TRIANGLES,24, GL_UNSIGNED_INT, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	GLCall(glUseProgram(0));
}