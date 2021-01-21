cmake_minimum_required(VERSION 3.10)
project(YourCraft)

set(LIBS_PATH libs)
set(SOURCE_PATH src)

# setup glad
add_library(GLAD
  ${LIBS_PATH}/glad/src/glad.c
  ${LIBS_PATH}/glad/include/glad/glad.h
)
set(GLAD_INCLUDE_DIRECTORY ${LIBS_PATH}/glad/include/)

set(_GLFW_X11 1)
find_package(Threads)
add_subdirectory(${LIBS_PATH}/glfw/src/)
set(GLFW_INCLUDE_DIRECTORY ${LIBS_PATH}/glfw/include/)

add_subdirectory(${LIBS_PATH}/glm)
set(GLM_INCLUDE_DIRECTORY ${LIBS_PATH}/glm/)



add_executable(${PROJECT_NAME}
  ${SOURCE_PATH}/gamecontext.cpp
  ${SOURCE_PATH}/gamecontext.h
)

include_directories(${GLAD_INCLUDE_DIRECTORY} ${GLM_INCLUDE_DIRECTORY} ${GLFW_INCLUDE_DIRECTORY})
target_link_libraries(${PROJECT_NAME} GLAD glfw dl)