#pragma once

#include <inttypes.h>
#include <glm/glm.hpp>

enum{
    BLOCK_GRASS = 0,
    BLOCK_DIRT,
    NUM_BLOCKS
};

struct CBlockTexture{
    uint32_t m_aTextures[3]; // bottom, middle, top
    glm::vec3 m_aColors[3];

    CBlockTexture(uint32_t Top, glm::vec3 TopColor, uint32_t Middle, glm::vec3 MiddleColor, uint32_t Bottom, glm::vec3 BottomColor){
        m_aTextures[0] = Bottom;
        m_aColors[0] = BottomColor;

        m_aTextures[1] = Middle;
        m_aColors[1] = MiddleColor;

        m_aTextures[2] = Top;
        m_aColors[2] = TopColor;
    }
};

struct CBlockInfo{
    glm::mat4 m_Pos;
    unsigned int m_Type;
};

class CBlock{
private:
    uint32_t m_BlockPosUniform;
    uint32_t m_PlayerViewUniform;
    uint32_t m_ProjectionUniform;
    uint32_t m_ColorUniform;

    uint32_t m_VAO;
    uint32_t m_VBO;
    
    CBlockTexture m_Textures;
    class CGameContext* m_pGameContext;

public:
    CBlock(class CGameContext* pGameContext, CBlockTexture Textures);
    ~CBlock();

    void Render(glm::mat4& Pos);
};