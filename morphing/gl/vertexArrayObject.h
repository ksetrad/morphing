//
// Created by idalov on 09.11.2020.
//

#ifndef GL_VERTEXARRAYOBJECT_H
#define GL_VERTEXARRAYOBJECT_H

#include <GL/glew.h>

namespace gl
{
	/// \brief VAO
	class VertexArrayObject
	{
		public:
			/// \brief Конструктор
			VertexArrayObject ();

			/// \brief Деструктор
			virtual
			~VertexArrayObject();

			///\brief Привязать VAO как активный
			void
			bind () const;

			///\brief Отвязать VAO
			void
			release () const;

			/// \brief Установить параметры атрибута в буфере
			/// \param layout позиция привязки атрибута в шейдере
			/// \param len длина блока данных атрибута
			/// \param type тип данных в блоке
			/// \param size полная длина блока данных в буфере
			/// \param offset позиция блока данных атрибута в исходном блоке данных (сдвиг)
			void
			setAttributePointer (
					int layout,
					size_t len,
					GLenum type,
					size_t size,
					int offset
			);

		private:
			/// Дескриптор
			GLuint descriptor { 0 };

	};
}
#endif //GL_VERTEXARRAYOBJECT_H
