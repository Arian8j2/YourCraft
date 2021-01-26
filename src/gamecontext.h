#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <inttypes.h>

#include "color.h"
#include "block.h"

#define ANTIALIASING
// #define V_SYNC

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class CGameContext{
private:
    GLFWwindow* m_pWindow;
    uint32_t m_BlockProgram;

    class CPlayer* m_pPlayer;
    class CTextRenderer* m_pTextRenderer;

    class CTexture* m_apBlockTexs[3];
    class CBlock* m_apBlocks[NUM_BLOCKS];
    std::vector<CBlockInfo> m_aBlockInfos;

    void Inputs();
    void Render();

public:
    CGameContext();
    ~CGameContext();
    
    void Run();

    uint32_t GetBlockProgram() const { return m_BlockProgram; }
    class CPlayer* GetPlayer() const { return m_pPlayer; }
    GLFWwindow* GetWindow() { return m_pWindow; }
};