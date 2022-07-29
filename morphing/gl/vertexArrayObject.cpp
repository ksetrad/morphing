//
// Created by idalov on 09.11.2020.
//

#include "gl/vertexArrayObject.h"

using namespace gl;

VertexArrayObject::VertexArrayObject ()
{
	glGenVertexArrays ( 1, &descriptor );
}

void
VertexArrayObject::bind () const
{
	glBindVertexArray ( descriptor );
}

void
VertexArrayObject::release () const
{
	glBindVertexArray ( 0 );
}

void
VertexArrayObject::setAttributePointer (
		int layout,
		size_t len,
		GLenum type,
		size_t size,
		int offset
)
{
	/// Привязываем VAO как активный
	bind();
	/// Устанавливаем параметры атрибута и активируем его
	glVertexAttribPointer ( layout, len, type, GL_FALSE, size, reinterpret_cast<GLvoid *>(offset) );
	glEnableVertexAttribArray ( layout );
}

VertexArrayObject::~VertexArrayObject ()
{
	glDeleteVertexArrays ( 1, &descriptor );
}
