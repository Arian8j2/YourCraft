#include "gamecontext.h"
#include "shader.h"
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

    m_Width = GetSettingValue("width").GetInt();
    m_Height = GetSettingValue("height").GetInt();

    if(!glfwInit()){
        fprintf(stderr, "Error, Cannot initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(GetSettingValue("anti_aliasing").GetBool())
        glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if(!GetSettingValue("v-sync").GetBool())
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);


    m_pWindow = glfwCreateWindow(m_Width, m_Height, "YourCraft", GetSettingValue("fullscreen").GetBool()? glfwGetPrimaryMonitor(): 0, 0);
    glfwMakeContextCurrent(m_pWindow);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        fprintf(stderr, "Error, Failed to load GLAD\n");
        return;
    }

    glViewport(0, 0, m_Width, m_Height);
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

    CBlockTexture TexBuffer(m_apBlockTexs[2]->GetValue(), glm::vec3(0.496f, 0.697f, 0.300f), m_apBlockTexs[0]->GetValue(), glm::vec3(1.0f, 1.0f, 1.0f), m_apBlockTexs[1]->GetValue(), glm::vec3(1.0f, 1.0f, 1.0f));
    m_apBlocks[BLOCK_GRASS] = new CBlock(this, TexBuffer);

    TexBuffer = CBlockTexture(m_apBlockTexs[1]->GetValue(), glm::vec3(1.0f, 1.0f, 1.0f), m_apBlockTexs[1]->GetValue(), glm::vec3(1.0f, 1.0f, 1.0f), m_apBlockTexs[1]->GetValue(), glm::vec3(1.0f, 1.0f, 1.0f));
    m_apBlocks[BLOCK_DIRT] = new CBlock(this, TexBuffer);


    glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(m_pWindow, OnMouseMove);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 BasePos(1.0f);
    CBlockInfo BlockInfoBuffer;

    for(int y=0; y < 3; y++){
        for(int i=0; i < 16; i++){
            for(int j=0; j < 16; j++){
                BlockInfoBuffer.m_Pos = glm::translate(BasePos, glm::vec3(j, -y, i));
                BlockInfoBuffer.m_Type = y==0?BLOCK_GRASS: BLOCK_DIRT;
                m_aBlockInfos.push_back(BlockInfoBuffer);
            }
        }
    }

    m_pTextRenderer = new CTextRenderer(this);
}

void CGameContext::Run(){
    char aFPSCounter[12] = "counting...";
    bool ShowFPS = GetSettingValue("show_fps").GetBool();

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
        for(CBlockInfo& BlockInfo: m_aBlockInfos){
            m_apBlocks[BlockInfo.m_Type]->Render(BlockInfo.m_Pos);
        }

        // display FPS
        if(ShowFPS){
            static RGBAColor s_FPSCounterColor(0, 0, 0, 255);
            m_pTextRenderer->RenderText(aFPSCounter, 15.0f, (float)m_Height - 40.0f, 0.7f, s_FPSCounterColor);
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

    for(int i=0; i < NUM_BLOCKS; i++)
        delete m_apBlocks[i];
    
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