//
// Created by idalov on 09.11.2020.
//

#ifndef SCENE_SHAPE_H
#define SCENE_SHAPE_H

#include <glm/glm.hpp>

#include <vector>

namespace scene
{
	/// Форма плоского объекта
	struct Shape
	{
		/// Массив вершин
		std::vector <glm::vec2> vertexes;
		/// Массив индексов
		std::vector <unsigned int> indices;
	};
}
#endif //SCENE_SHAPE_H
