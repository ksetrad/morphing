//
// Created by idalov on 09.11.2020.
//

#ifndef SCENE_MORPHINGMODEL_H
#define SCENE_MORPHINGMODEL_H

#include "gl/vertexArrayObject.h"

#include "scene/shape.h"

namespace scene
{
	/// Изоморфная модель: модель переходящая между схожими по свойствам формами во времени
	class MorphingModel
	{
		public:
			/// \brief Конструктор
			/// \param first Первая форма
			/// \param second Вторая форма
			MorphingModel (
					const Shape & first,
					const Shape & second
			);

			/// \brief Функция отрисовки модели
			void
			draw ();

		private:
			/// VAO
			gl::VertexArrayObject vao;

			/// Размер элементного буфера
			size_t size;
	};
}
#endif //SCENE_MORPHINGMODEL_H
