//
// Created by idalov on 09.11.2020.
//
#include "scene.h"
#include "scene/eventManager.h"

using namespace scene;

EventManager::EventManager ( Scene * scene ) : scene ( scene )
{

}

bool
EventManager::pollEvent ()
{
	/// SDL событие
	SDL_Event event { };
	/// Обрабатываем SDL события в пуле пока они есть
	while ( SDL_PollEvent ( &event ) )
	{
		/// Начинаем обработку события
		switch ( event.type )
		{
			case SDL_QUIT:
				/// Если произошло событие закрытия окна, то сообщаем что надо завершить программу
				return false;
			case SDL_KEYDOWN:
				// Если нажата клавиша
				switch ( event.key.keysym.sym )
				{
					/// Клавиша ESC
					case SDLK_ESCAPE:
						/// Сообщаем что надо завершить программу
						return false;
				}
				break;
		}
	}
	return true;
}
