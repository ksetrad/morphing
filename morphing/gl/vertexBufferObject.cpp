//
// Created by idalov on 09.11.2020.
//



#include "gl/vertexBufferObject.h"

using namespace gl;

VertexBufferObject::VertexBufferObject (
		const VertexBufferObject::Types & e_type,
		const void * data,
		const size_t & size
)
{
	glGenBuffers ( 1, &descriptor );
	type = ( e_type == VERTEXES ) ? GL_ARRAY_BUFFER : GL_ELEMENT_ARRAY_BUFFER;
	glBindBuffer ( type, descriptor );
	glBufferData ( type, size, data, GL_STATIC_DRAW );
}


VertexBufferObject::~VertexBufferObject ()
{
	glDeleteBuffers ( 1, &descriptor );

}