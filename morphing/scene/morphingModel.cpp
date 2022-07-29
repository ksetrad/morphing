//
// Created by idalov on 09.11.2020.
//
#include "gl/vertexBufferObject.h"
#include "scene/morphingModel.h"

using namespace scene;

MorphingModel::MorphingModel (
		const Shape & first,
		const Shape & second
)
{
	/// Строим единый буфер вершин по двум формам
	std::vector <glm::vec2> vertexes ( second.vertexes.size () * 2 );
	for ( int i = 0 ;
	      i < 2 * first.vertexes.size () - 1 ;
	      i += 2 )
	{
		size_t id = i / 2;
		vertexes[ i ] = first.vertexes[ id ];
		vertexes[ i + 1 ] = second.vertexes[ id ];
	}
	vao.bind ();
	auto vbo = new gl::VertexBufferObject ( gl::VertexBufferObject::VERTEXES, vertexes.data (),
	                                        vertexes.size () * sizeof ( glm::vec2 ) );

	/// И устанавливаем соответствующие атрибуты в шейдере для каждой из форм
	vao.setAttributePointer ( 0, 2, GL_FLOAT, 2 * sizeof ( glm::vec2 ), 0 );
	vao.setAttributePointer ( 1, 2, GL_FLOAT, 2 * sizeof ( glm::vec2 ), 8 );
	/// Формируем элементный буфер
	auto ibo = new gl::VertexBufferObject ( gl::VertexBufferObject::INDICES, first.indices.data (),
	                                        first.indices.size () * sizeof ( unsigned int) );
	vao.release ();
	/// Удаляем не нужные более буферы
	delete ibo;
	delete vbo;
	/// Сохраняем количество индексов в элементном буфере
	size = first.indices.size ();
}

void
MorphingModel::draw ()
{
	vao.bind ();
	glDrawElements ( GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr );
	vao.release ();
}
