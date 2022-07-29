//
// Created by idalov on 09.11.2020.
//
#include <fstream>
#include <cassert>
#include "gl/shaderProgram.h"

using namespace gl;

ShaderProgram::ShaderProgram ()
{
	descriptor = glCreateProgram ();
}

void
ShaderProgram::addFromFile (
		const ShaderProgram::ShaderTypes & type,
		const char * path
)
{
	std::ifstream file ( path );
	/// Как-то проверяем что файл открыт
	assert( file.is_open () );
	/// Считываем файл в строку
	std::string str ( ( std::istreambuf_iterator <char> ( file ) ),
	                  std::istreambuf_iterator <char> () );
	const char * code = str.c_str ();
	/// Дескриптор создаваемого шейдера
	GLint shader_descriptor;
	shader_descriptor = glCreateShader ( ( type == VERTEX ) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER );
	/// Создание шейдера заданного типа по исходному коду
	glShaderSource ( shader_descriptor, 1, &code, nullptr );
	/// Компиляция
	glCompileShader ( shader_descriptor );

	/// Как-то проверяем успешность компиляции
	GLint success;
	glGetShaderiv ( shader_descriptor, GL_COMPILE_STATUS, &success );
	assert( success );

	/// Привязка к шейдерной программе
	glAttachShader ( descriptor, shader_descriptor );
	using_shaders.emplace_back ( shader_descriptor );
}

void
ShaderProgram::link ()
{
	/// Линкуем программу
	glLinkProgram ( descriptor );
	/// Как-то проверяем успешность линковки
	GLint success;
	glGetProgramiv ( descriptor, GL_LINK_STATUS, &success );
	assert( success );
	/// Удаляем ненужные шейдеры после линковки программы
	for ( const auto & shader_descriptor : using_shaders )
		glDeleteShader ( shader_descriptor );
	using_shaders.clear();
}

void
ShaderProgram::bind () const
{
	glUseProgram ( descriptor );
}

void
ShaderProgram::release () const
{
	glUseProgram ( 0 );
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram ( descriptor );
}
