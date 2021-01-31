#include "block.h"
#include "gamecontext.h"
#include "player.h"

CBlock::CBlock(CGameContext* pGameContext, CBlockTexture Textures): m_pGameContext(pGameContext), m_Textures(Textures){
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    const static float aVerticies[] = {
        // sides
        //  front
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        //  left
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        //  right
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        //  back
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,


        //bottom
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,


        //top
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
    };

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVerticies), aVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*5, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*5, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    m_BlockPosUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uBlockPos");
    m_PlayerViewUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uView");
    m_ProjectionUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uProjection");
    m_ColorUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uColor");
}

void CBlock::Render(glm::vec3& Pos){
    glm::mat4 MatPos(1.0f);
    MatPos[3] = glm::vec4(Pos, 1.0f);

    static glm::mat4 s_Projection = glm::perspective(glm::radians((float) m_pGameContext->GetSettingValue("fov").GetInt()), (float)m_pGameContext->m_Width / m_pGameContext->m_Height, 0.1f, 100.0f);

    glBindVertexArray(m_VAO);
    glUniformMatrix4fv(m_BlockPosUniform, 1, 0, glm::value_ptr(MatPos));
    glUniformMatrix4fv(m_PlayerViewUniform, 1, 0, glm::value_ptr(m_pGameContext->GetPlayer()->m_View));
    glUniformMatrix4fv(m_ProjectionUniform, 1, 0, glm::value_ptr(s_Projection));
    

    glUniform3f(m_ColorUniform, m_Textures.m_aColors[1].r, m_Textures.m_aColors[1].g, m_Textures.m_aColors[1].b);
    glBindTexture(GL_TEXTURE_2D, m_Textures.m_aTextures[1]);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 24);

    glUniform3f(m_ColorUniform, m_Textures.m_aColors[0].r, m_Textures.m_aColors[0].g, m_Textures.m_aColors[0].b);
    glBindTexture(GL_TEXTURE_2D, m_Textures.m_aTextures[0]);
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glUniform3f(m_ColorUniform, m_Textures.m_aColors[2].r, m_Textures.m_aColors[2].g, m_Textures.m_aColors[2].b);
    glBindTexture(GL_TEXTURE_2D, m_Textures.m_aTextures[2]);
    glDrawArrays(GL_TRIANGLES, 30, 6);
}

CBlock::~CBlock(){
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}