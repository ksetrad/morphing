//
// Created by idalov on 09.11.2020.
//

#include "scene/shapeFactory.h"

using namespace scene;

ShapeFactory::ShapeFactory(
		const size_t & v_vertexCount,
		const float & radius
) : vertex_count ( v_vertexCount * 4 + 1 ), radius ( radius ) {}

Shape ShapeFactory::constructRing ()
{
		return construct ( [ this ] ( float angle )
		                   {return radius * glm::vec2{std::cos ( angle ), std::sin ( angle ) };}
		);
}

Shape ShapeFactory::constructRect ()
{
	/* Это конечно грубо, но очень уж хотелось */
	return construct ( [ this ] ( float angle )
	                   {
		                   if ( angle >= ( M_PI * 2 - M_PI_4 ) || angle < M_PI_4 )
		                   {
			                   return radius * glm::vec2 { 1, std::tan ( angle ) };
		                   }
		                   else if ( angle >= M_PI_4 && angle < ( M_PI_2 + M_PI_4 ) )
		                   {
			                   return radius * glm::vec2 { 1 / std::tan ( angle ), 1 };
		                   }
		                   else if ( angle >= ( M_PI_2 + M_PI_4 ) && angle < ( M_PI + M_PI_4 ) )
		                   {
			                   return radius * glm::vec2 { -1, -std::tan ( angle ) };
		                   }
		                   else
		                   {
			                   return radius * glm::vec2 { -1 / std::tan ( angle ), -1 };
		                   }
	                   }
	);
}

Shape ShapeFactory::construct ( const std::function <glm::vec2 ( float )>& calFunction ) const
{
	Shape result;
	result.vertexes.resize ( vertex_count );
	result.indices.resize ( ( vertex_count - 1 ) * 3 );
	/// Устанавливаем 0 вую вершину в центр
	result.vertexes[ 0 ] = glm::vec2 ( 0 );
	/// Устанавливаем первую вершину для угла поворота 0 градусов
	result.vertexes[ 1 ] = glm::vec2 ( radius, 0 );

	/// Вычисляем шаг по углу
	float delta = M_PI * 2 / ( vertex_count - 2 );
	for ( int i = 2, j = 2 ;
	      i < vertex_count ;
	      i++, j += 3 )
	{
		float angle = delta * ( i - 1 );
		result.vertexes[ i ] = calFunction ( angle );
		result.indices[ j - 2 ] = 0;
		result.indices[ j - 1 ] = i - 1;
		result.indices[ j ] = i;
	}
	/// "замыкаем фигуру по кругу, соединяя последнюю вершину с первыми
	result.indices[ ( vertex_count - 2 ) * 3 ] = 0;
	result.indices[ ( vertex_count - 2 ) * 3 + 1 ] = vertex_count - 1;
	result.indices[ ( vertex_count - 2 ) * 3 + 2 ] = 1;

	return result;
}