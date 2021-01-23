#include "gamecontext.h"
#include "shader.h"
#include "block.h"
#include "texture.h"

static void OnWindowSizeChange(GLFWwindow* pWindow, int Width, int Height){
    glViewport(0, 0, Width, Height);
}

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
    glfwSetFramebufferSizeCallback(m_pWindow, OnWindowSizeChange);

    // create block shaders and program
    m_BlockProgram = glCreateProgram();

    try{
        CShader* pBlockVertSh = new CShader("block.vert", GL_VERTEX_SHADER);
        CShader* pBlockFragSh = new CShader("block.frag", GL_FRAGMENT_SHADER);

        glAttachShader(m_BlockProgram, pBlockVertSh->GetValue());
        glAttachShader(m_BlockProgram, pBlockFragSh->GetValue());
        glLinkProgram(m_BlockProgram);

        delete pBlockVertSh;
        delete pBlockFragSh;

    }catch(int& Failure){
        glfwSetWindowShouldClose(m_pWindow, true);
        return;
    }
}

void CGameContext::Run(){
    m_pTexGrass = new CTexture("grass_block_side");
    CBlock* pBlock = new CBlock(this, glm::mat4(1.0f), CBlockTexture(m_pTexGrass->GetValue(), m_pTexGrass->GetValue(), m_pTexGrass->GetValue()));

    while(!glfwWindowShouldClose(m_pWindow)){
        Inputs();
        Render();
        pBlock->Render();

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    delete pBlock;
    delete m_pTexGrass;
    delete this;
}

CGameContext::~CGameContext(){
    glDeleteProgram(m_BlockProgram);
    glfwTerminate();
}

void CGameContext::Inputs(){
    if(glfwGetKey(m_pWindow, GLFW_KEY_Q))
        glfwSetWindowShouldClose(m_pWindow, true);
}

void CGameContext::Render(){
    static RGBAColor SkyColor(115, 204, 255);
    glClearColor(SkyColor.r, SkyColor.g, SkyColor.b, SkyColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_BlockProgram);
}

int main(){
    CGameContext* pGameContext = new CGameContext();
    pGameContext->Run();

    return 0;
}