//
// Created by idalov on 09.11.2020.
//

#ifndef GL_SHADERPROGRAM_H
#define GL_SHADERPROGRAM_H

#include <GL/glew.h>
#include <list>

namespace gl
{
	/// \brief Шейдерная программа
	class ShaderProgram
	{
		public:
			/// Типы шейдеров
			enum ShaderTypes
			{
				/// Вершинный
				VERTEX,
				/// Фрагментный
				FRAGMENT
			};

			/// \brief Конструктор
			ShaderProgram ();

                        /// \brief Деструктор
                        virtual
                        ~ShaderProgram();

			/// \brief Добавить шейдер из файла
			/// \param type Тип шейдера
			/// \param path путь к файлу
			void
			addFromFile (
					const ShaderTypes & type,
					const char * path
			);

			/// \brief Процедура линковки шейдерной программы
			void
			link ();

			/// \brief Процедура привязки шейдерной программы
			void
			bind () const;

			/// \brief Процедура отключения шейдерной программы
			void
			release () const;

		private:
			/// Дескриптор шейдерной программы
			GLuint descriptor;

			/// Массив дескрипторов используемых шейдеров
			std::list<GLint> using_shaders;
	};
}
#endif //GL_SHADERPROGRAM_H
