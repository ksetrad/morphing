//
// Created by idalov on 09.11.2020.
//

#include <glm/gtc/type_ptr.hpp>

#include <cassert>
#include <mutex>
#include <GL/glew.h>

#include "gl/shaderProgram.h"

#include "scene/morphingModel.h"
#include "scene/shapeFactory.h"

#include "scene.h"

Scene::Scene (
		const int & width,
		const int & height
) : window ( nullptr ), eventManager ( this ), size ( width, height )
{
	/// Инициализируем SDL2
	assert ( !( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) );

	/// Устанавливаем используемую версию OpenGL (3.3)
	SDL_GL_SetAttribute ( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute ( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	SDL_GL_SetAttribute ( SDL_GL_DEPTH_SIZE, 8 );
	SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute ( SDL_GL_MULTISAMPLESAMPLES, 8 );

	/// Создаем окно
	window = SDL_CreateWindow ( "Тестовое задание", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
	                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

	/// Проверяем наличие окна
	assert ( window != nullptr );
}

void
Scene::show ()
{
	/// Инициализируем цикл рендеринга на отдельном потоке
	renderThread = std::make_unique <std::thread> ( &Scene::renderLoop, this );

	/// Дожидаемся завершения инициализации рендеринга
	std::unique_lock <std::mutex> lock ( renderingState.drawMutex );
	renderingState.cv.wait ( lock, [ this ]
	{
		return renderingState.ready;
	} );

	/// Запускаем цикл обработки событий
	while ( eventManager.pollEvent () )
	{

	}

	/// Отключаем рендеринг и дожидаемся завершения
	renderingState.isRendered = false;
	if ( renderThread->joinable () )
	{
		renderThread->join ();
	}

	/// Выключаем SDL
	SDL_Quit ();
}

void
Scene::renderLoop ()
{
	/// создаем контекст OpenGL
	context = std::make_unique <sdl2::Context> ( window );
	/// Собираем шейдерную программу
	gl::ShaderProgram shaderProgram;
	shaderProgram.addFromFile ( gl::ShaderProgram::VERTEX, "./res/shaders/main.vert" );
	shaderProgram.addFromFile ( gl::ShaderProgram::FRAGMENT, "./res/shaders/main.frag" );
	shaderProgram.link ();

	/// Настраиваем OpenGL
	/// Цвет фона по умолчанию (черный)
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	// Включаем тест глубины
	glEnable ( GL_DEPTH_TEST );
	/// Сообщаем о завершении подготовки рендеринга
	{
		std::unique_lock <std::mutex> lock ( renderingState.drawMutex );
		renderingState.ready = true;
		renderingState.cv.notify_all ();
	}

	/// Инициализируем фабрику моделей
	scene::ShapeFactory factory ( 128, 0.5 );
	/// Создаем изоморфную модель между кругом и прямоугольником
	scene::MorphingModel morphingModel( factory.constructRect (), factory.constructRing () );
	shaderProgram.bind ();
	glm::mat4 proj = glm::ortho ( -1.f, 1.f, -float ( size.y ) / size.x, float ( size.y ) / size.x );
	glUniformMatrix4fv ( 3, 1, GL_FALSE, glm::value_ptr ( proj ) );
	shaderProgram.release ();
	/// Запускаем рендеринг
	renderingState.isRendered = true;
	while ( renderingState.isRendered )
	{
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		shaderProgram.bind ();
		/// Меняем фактор морфинга t от 0 до 1 по закону синуса за 1 сек используя время в милисекундах
		glUniform1f ( 2, ( std::sin (
				( ( std::chrono::system_clock::now ().time_since_epoch ().count () / 1000000 ) % 1000 ) * M_PI / 500 ) +
		                   1 ) / 2.f );
		morphingModel.draw ( );
		shaderProgram.release ();
		/// Завершаем операцию рендеринга
		SDL_GL_SwapWindow ( window );
	}
}