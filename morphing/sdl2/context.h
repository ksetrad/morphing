//
// Created by idalov on 09.11.2020.
//

#ifndef SDL2_CONTEXT_H
#define SDL2_CONTEXT_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace sdl2
{
	/// \brief Контекст SDL2
	class Context
	{
		public:
			/// Конструктор
			explicit
			Context ( SDL_Window * window )
			{
				/// создаем контекст OpenGL
				context = SDL_GL_CreateContext ( window );
				/// Инициализируем GLEW
				glewInit ();
			}

			virtual ~Context ()
			{
				SDL_GL_DeleteContext ( context );
			}

			/// Сделать контекст активным
			void
			makeCurrent ()
			{
				SDL_GL_MakeCurrent ( window, context );
			}

		private:
			/// Контекст
			void * context;

			/// Окно
			SDL_Window * window;

	};
}
#endif //SDL2_CONTEXT_H