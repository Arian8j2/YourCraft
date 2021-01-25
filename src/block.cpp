#include "block.h"
#include "gamecontext.h"
#include "player.h"

CBlock::CBlock(CGameContext* pGameContext, glm::mat4 Pos, CBlockTexture Textures): m_pGameContext(pGameContext), m_Pos(Pos), m_Textures(Textures){
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    const static float aVerticies[] = {
        // sides
        //  front
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        //  left
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        //  right
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        //  back
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,


        //bottom
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,


        //top
        -0.5f,  0.5f,  0.5f,  0.496f, 0.697f, 0.300f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.496f, 0.697f, 0.300f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.496f, 0.697f, 0.300f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.496f, 0.697f, 0.300f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.496f, 0.697f, 0.300f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.496f, 0.697f, 0.300f,  0.0f, 1.0f,
    };

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aVerticies), aVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*8, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float)*8, (void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);

    m_BlockPosUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uBlockPos");
    m_PlayerViewUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uView");
    m_ProjectionUniform = glGetUniformLocation(pGameContext->GetBlockProgram(), "uProjection");
}

void CBlock::Render(){
    static glm::mat4 s_Projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    glBindVertexArray(m_VAO);
    glUniformMatrix4fv(m_BlockPosUniform, 1, 0, glm::value_ptr(m_Pos));
    glUniformMatrix4fv(m_PlayerViewUniform, 1, 0, glm::value_ptr(m_pGameContext->GetPlayer()->m_View));
    glUniformMatrix4fv(m_ProjectionUniform, 1, 0, glm::value_ptr(s_Projection));
    
    glBindTexture(GL_TEXTURE_2D, m_Textures.m_Middle);
    glActiveTexture(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 24);

    glBindTexture(GL_TEXTURE_2D, m_Textures.m_Bottom);
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glBindTexture(GL_TEXTURE_2D, m_Textures.m_Top);
    glDrawArrays(GL_TRIANGLES, 30, 6);
}

CBlock::~CBlock(){
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}