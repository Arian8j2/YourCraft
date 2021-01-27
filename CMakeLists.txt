cmake_minimum_required(VERSION 3.10)
project(YourCraft)

set(LIBS_PATH libs)
set(SOURCE_PATH src)

add_library(GLAD
  ${LIBS_PATH}/glad/src/glad.c
  ${LIBS_PATH}/glad/include/glad/glad.h
)
set(GLAD_INCLUDE_DIRS ${LIBS_PATH}/glad/include/)

set(_GLFW_X11 1)
find_package(Threads)
add_subdirectory(${LIBS_PATH}/glfw/)
set(GLFW_INCLUDE_DIRS ${LIBS_PATH}/glfw/include/)

add_subdirectory(${LIBS_PATH}/glm)
set(GLM_INCLUDE_DIRS ${LIBS_PATH}/glm/)

set(STB_INCLUDE_DIRS ${LIBS_PATH}/stb)

add_subdirectory(${LIBS_PATH}/freetype2)
set(FREETYPE_INCLUDE_DIRS ${LIBS_PATH}/freetype2/include)

add_executable(${PROJECT_NAME}
  ${SOURCE_PATH}/gamecontext.cpp
  ${SOURCE_PATH}/gamecontext.h
  ${SOURCE_PATH}/shader.cpp
  ${SOURCE_PATH}/shader.h
  ${SOURCE_PATH}/color.cpp
  ${SOURCE_PATH}/color.h
  ${SOURCE_PATH}/block.cpp
  ${SOURCE_PATH}/block.h
  ${SOURCE_PATH}/texture.cpp
  ${SOURCE_PATH}/texture.h
  ${SOURCE_PATH}/player.cpp
  ${SOURCE_PATH}/player.h
  ${SOURCE_PATH}/text.cpp
  ${SOURCE_PATH}/text.h
  ${SOURCE_PATH}/collision.cpp
  ${SOURCE_PATH}/collision.h
)

function(copy_dir DIR_NAME)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/${DIR_NAME}/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DIR_NAME})
endfunction()

copy_dir(shaders)
copy_dir(textures)
copy_dir(fonts)

include_directories(${GLAD_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${STB_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GLAD glfw dl freetype)