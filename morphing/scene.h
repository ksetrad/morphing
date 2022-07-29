//
// Created by idalov on 09.11.2020.
//

#ifndef _SCENE_H
#define _SCENE_H

#include <glm/glm.hpp>
#include <memory>
#include <thread>

#include <SDL2/SDL.h>
#include <condition_variable>
#include <atomic>

#include "sdl2/context.h"
#include "scene/eventManager.h"

class Scene
{
	public:
		/// \brief Сцена отображения
		/// \param width ширина
		/// \param height высота
		Scene (
				const int & width,
				const int & height
		);

		/// \brief запустить отрисовку
		void
		show ();

		/// \brief процедура рендеринга
		void
		renderLoop ();

	private:
		/// Окно для отображения сцены
		SDL_Window * window;

		/// Менеджер управкления событиями SDL
		scene::EventManager eventManager;

		/// Поток рендеринга
		std::unique_ptr <std::thread> renderThread { nullptr };

		/// \brief Состояние рендеринга
		struct
		{
			/// Флаг готовности к работе
			bool ready { false };
			/// Условная переменная
			std::condition_variable cv;
			/// Мьютекс отрисовки
			std::mutex drawMutex;
			/// Флаг работы
			std::atomic <bool> isRendered { false };
		} renderingState;

		/// Контекст
		std::unique_ptr <sdl2::Context> context { nullptr };

		/// Геометрические размеры окна
		glm::i32vec2 size;
};

#endif //_SCENE_H
