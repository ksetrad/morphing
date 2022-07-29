//
// Created by idalov on 09.11.2020.
//

#ifndef SCENE_SHAPEFACTORY_H
#define SCENE_SHAPEFACTORY_H

#include <functional>
#include "scene/shape.h"

namespace scene
{
	/// \brief Фабрика моделей (форм)
	class ShapeFactory {
		public:
			/// \brief Конструктор
			/// \param vertexCount количество врешин в порождаемых формах формах
			explicit ShapeFactory(
					const size_t & vertexCount,
					const float & radius
			);

			/// \brief Построить форму круга
			/// \return Форма
			Shape
			constructRing ();

			/// \brief Построить форму квадрата
			/// \return Форма
			Shape
			constructRect ();

		private:

			/// \brief Функция построения формы по заданному уравнению для вычисления вершин в зависимости от полярного угла
			/// \param calFunction Фукнция
			/// \return Вычисленная форма
			Shape
			construct(const std::function<glm::vec2(float angle)>& calFunction) const;

			/// Количество вершин в строимых моделях
			size_t vertex_count;

			/// Радиус круга/половина длины квадрата
			float radius;
	};
}
#endif //SCENE_SHAPEFACTORY_H
