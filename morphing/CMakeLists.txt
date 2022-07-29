cmake_minimum_required(VERSION 3.17)
project(morphing)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(project_dir ${CMAKE_SOURCE_DIR})

set(morphing_src
        ${project_dir}/scene.cpp
        ${project_dir}/scene/eventManager.cpp
        ${project_dir}/scene/morphingModel.cpp
        ${project_dir}/scene/shapeFactory.cpp
        ${project_dir}/gl/shaderProgram.cpp
        ${project_dir}/gl/vertexArrayObject.cpp
        ${project_dir}/gl/vertexBufferObject.cpp
        )

add_executable(morphing ${morphing_src} main.cpp)

target_include_directories(morphing PRIVATE ${SDL_INCLUDE_DIRS} ${project_dir})

if (UNIX)
    target_link_libraries(morphing SDL2 pthread GL GLEW::GLEW glm)
endif ()

if (MINGW)
    target_compile_definitions(morphing PRIVATE SDL_MAIN_HANDLED)
    target_link_libraries(morphing SDL2 pthread GLEW::GLEW glm)
endif ()

file(GLOB shaders
        scene/shaders/main.vert
        scene/shaders/main.frag
        )

file(COPY ${shaders} DESTINATION ${CMAKE_BINARY_DIR}/res/shaders)
