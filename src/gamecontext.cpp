#include "gamecontext.h"
#include "shader.h"
#include "block.h"
#include "texture.h"
#include "player.h"
#include "text.h"

static CGameContext* gs_GameContext;
static void OnWindowSizeChange(GLFWwindow* pWindow, int Width, int Height){
    glViewport(0, 0, Width, Height);
}

static void OnMouseMove(GLFWwindow* pWindow, double X, double Y){
    gs_GameContext->GetPlayer()->HandleMouseMovement(X, Y);
}


CGameContext::CGameContext(){
    gs_GameContext = this;

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

#ifndef V_SYNC
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
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

    m_pPlayer = new CPlayer(this);

    m_apBlockTexs[0] = new CTexture("grass_block_side");
    m_apBlockTexs[1] = new CTexture("dirt");
    m_apBlockTexs[2] = new CTexture("grass_block_top");

    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_pWindow, OnMouseMove);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 BasePos(1.0f);
    CBlockTexture GrassTexture(m_apBlockTexs[2]->GetValue(), m_apBlockTexs[0]->GetValue(), m_apBlockTexs[1]->GetValue());
    m_apBlocks.reserve(12*12);

    for(int i=0; i < 16; i++){
        for(int j=0; j < 16; j++){
            glm::mat4 Pos = glm::translate(BasePos, glm::vec3(j, 0.0f, i));
            m_apBlocks.push_back(new CBlock(this, Pos, GrassTexture));
        }
    }

    m_pTextRenderer = new CTextRenderer;
}

void CGameContext::Run(){
    char aFPSCounter[12] = "counting...";

    while(!glfwWindowShouldClose(m_pWindow)){
        static double s_LastTime = glfwGetTime();

        static int s_FrameCount = 0;
        static double s_FrameSecondExpire = glfwGetTime() + 1.0f;

        // measuring deltatime for input handling
        double CurTime = glfwGetTime();
        float DeltaTime = CurTime - s_LastTime;
        s_LastTime = CurTime;

        // counting FPS
        s_FrameCount++;
        if(CurTime >= s_FrameSecondExpire){
            snprintf(aFPSCounter, sizeof(aFPSCounter), "%d", s_FrameCount);
            s_FrameCount = 0;
            s_FrameSecondExpire = glfwGetTime() + 1.0f;
        }

        Inputs();
        Render();

        glUseProgram(m_BlockProgram);
        for(CBlock* pBlock: m_apBlocks){
            pBlock->Render();
        }

        // display FPS
        {
            static RGBAColor s_FPSCounterColor(0, 0, 0, 255);
            m_pTextRenderer->RenderText(aFPSCounter, 15.0f, WINDOW_HEIGHT - 40.0f, 0.7f, s_FPSCounterColor);
        }

        m_pPlayer->UpdateView();
        m_pPlayer->HandleInputs(std::min(DeltaTime, 1 / 140.0f));

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }

    delete this;
}

CGameContext::~CGameContext(){
    for(int  i=0; i < sizeof(m_apBlockTexs)/sizeof(m_apBlockTexs[0]); i++)
        delete m_apBlockTexs[i];
    delete m_pPlayer;
    delete m_pTextRenderer;

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
}

int main(){
    CGameContext* pGameContext = new CGameContext();
    pGameContext->Run();

    return 0;
}