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

# setup glfw
add_subdirectory(${LIBS_PATH}/glfw)


add_executable(${PROJECT_NAME}
  ${SOURCE_PATH}/gamecontext.cpp
  ${SOURCE_PATH}/gamecontext.h
)
include_directories(${GLAD_INCLUDE_DIRECTORY})
