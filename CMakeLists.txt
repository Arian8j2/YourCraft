cmake_minimum_required(VERSION 3.10)
project(YourCraft)

set(LIBS_PATH libs)
set(SOURCE_PATH src)

add_library(GLAD
  ${LIBS_PATH}/glad/src/glad.c
  ${LIBS_PATH}/glad/include/glad/glad.h
)
set(GLAD_INCLUDE_DIRECTORY ${LIBS_PATH}/glad/include/)

set(_GLFW_X11 1)
find_package(Threads)
add_subdirectory(${LIBS_PATH}/glfw/)
set(GLFW_INCLUDE_DIRECTORY ${LIBS_PATH}/glfw/include/)

add_subdirectory(${LIBS_PATH}/glm)
set(GLM_INCLUDE_DIRECTORY ${LIBS_PATH}/glm/)

set(STB_INCLUDE_DIRECTORY ${LIBS_PATH}/stb)

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
)

function(copy_dir DIR_NAME)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/${DIR_NAME}/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DIR_NAME})
endfunction()

copy_dir(shaders)
copy_dir(textures)

include_directories(${GLAD_INCLUDE_DIRECTORY} ${GLM_INCLUDE_DIRECTORY} ${GLFW_INCLUDE_DIRECTORY} ${STB_INCLUDE_DIRECTORY})
target_link_libraries(${PROJECT_NAME} GLAD glfw dl)