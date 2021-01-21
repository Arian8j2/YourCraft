#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstring>
#include <cstdio>

#define ANTIALIASING

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class CGameContext{
private:
    GLFWwindow* m_pWindow;


public:
    CGameContext();
    ~CGameContext();
    
    void Run();
};