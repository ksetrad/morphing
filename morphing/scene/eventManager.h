//
// Created by idalov on 09.11.2020.
//

#ifndef SCENE_EVENTMANGER_H
#define SCENE_EVENTMANGER_H

#include <SDL2/SDL.h>

class Scene;

namespace scene
{
	/// \brief Менеджер обработки SDL событий
	class EventManager
	{
		public:
			/// \brief Конструктор
			/// \param scene сцена - родитель
			explicit
			EventManager ( Scene * scene );

			/// \brief Функция обработки событий
			/// \return true - события обработаны, можно продолжать работу. false - обработано событие завершения работы
			bool
			pollEvent ();

		private:
			/// Указатель на сцену - родителя
			Scene * scene { nullptr };
	};
}
#endif //SCENE_EVENTMANGER_H
