#include "block.h"


Voxel::Voxel()
{
	glGenVertexArrays(1,&_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(_indices),
		_indices,
		GL_STATIC_DRAW
	);
	
	glGenBuffers(1,&_VBO);
	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(_vertices),
		_vertices,
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(_vertices[0]) * 3,
		0
	);
	
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Voxel::~Voxel()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1,&_IBO);
	glDeleteBuffers(1, &_VBO);
}

