#include "gamecontext.h"

CGameContext::CGameContext(){
    if(!glfwInit()){
        fprintf(stderr, "Error, Cannot initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef ANTIALIASING
    glfwWindowHint(GLFW_SAMPLES, 4);
#endif

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "YourCraft", 0, 0);
    glfwMakeContextCurrent(m_pWindow);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        fprintf(stderr, "Error, Failed to load GLAD\n");
        return;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void CGameContext::Run(){
    while(!glfwWindowShouldClose(m_pWindow)){


        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    delete this;
}

CGameContext::~CGameContext(){
    glfwTerminate();
}

int main(){
    CGameContext* pGameContext = new CGameContext();
    pGameContext->Run();

    return 0;
}