//
// Created by idalov on 09.11.2020.
//

#ifndef GL_VERTEXBUFFEROBJECT_H
#define GL_VERTEXBUFFEROBJECT_H

#include <cstdlib>

#include <GL/glew.h>

namespace gl
{
	/// \brief Вершинный буфер
	class VertexBufferObject
	{
		public:
			/// Типы буфера
			enum Types
			{
				/// Вершинный буфер (vbo)
				VERTEXES,
				/// Элементный буфер (ibo)
				INDICES
			};

			/// \brief Конструктор
			/// \param type тип буфера
			/// \param data данные
			/// \param size размер данный
			VertexBufferObject (
					const Types & type,
					const void * data,
					const size_t & size
			);

			/// \brief Деструктор
			virtual
			~VertexBufferObject ();


		private:
			/// Дескриптор
			GLuint descriptor;

			/// Тип буфера
			GLenum type;
	};
}
#endif //GL_VERTEXBUFFEROBJECT_H
