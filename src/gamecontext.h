#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <cstdio>
#include <inttypes.h>

#include "color.h"

#define ANTIALIASING

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class CGameContext{
private:
    GLFWwindow* m_pWindow;
    uint32_t m_BlockProgram;

    class CTexture* m_pTexGrass;

    void Inputs();
    void Render();

public:
    CGameContext();
    ~CGameContext();
    
    void Run();

    uint32_t GetBlockProgram() const { return m_BlockProgram; }
};