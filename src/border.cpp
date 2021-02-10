#include "border.h"
#include "player.h"

CBorder::CBorder(CGameContext* pGameContext): m_pGameContext(pGameContext){
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    float aVerticies[] = {
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(aVerticies), aVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float)*3, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*3, 0);
    glEnableVertexAttribArray(1);
    
    glLineWidth(1.5f);
}

void CBorder::Render(glm::vec3& Pos){
    glUseProgram(m_pGameContext->GetBlockProgram());

    static uint32_t s_BlockPosUniform = glGetUniformLocation(m_pGameContext->GetBlockProgram(), "uBlockPos");
    static uint32_t s_PlayerViewUniform = glGetUniformLocation(m_pGameContext->GetBlockProgram(), "uView");
    static uint32_t s_ProjectionUniform = glGetUniformLocation(m_pGameContext->GetBlockProgram(), "uProjection");
    static uint32_t s_ColorUniform = glGetUniformLocation(m_pGameContext->GetBlockProgram(), "uColor");

    glm::mat4 MatPos(1.0f);
    MatPos[3] = glm::vec4(Pos, 1.0f);

    static glm::mat4 s_Projection = glm::perspective(glm::radians((float) m_pGameContext->GetSettingValue("fov").GetInt()), (float)m_pGameContext->m_Width / m_pGameContext->m_Height, 0.101f, 100.0f);

    glBindVertexArray(m_VAO);
    glUniformMatrix4fv(s_BlockPosUniform, 1, 0, glm::value_ptr(MatPos));
    glUniformMatrix4fv(s_PlayerViewUniform, 1, 0, glm::value_ptr(m_pGameContext->GetPlayer()->m_View));
    glUniformMatrix4fv(s_ProjectionUniform, 1, 0, glm::value_ptr(s_Projection));
    glUniform3f(s_ColorUniform, 0.0f, 0.0f, 0.0f);

    glBindVertexArray(m_VAO);
    
    for(int i=0; i < 4; i++)
        glDrawArrays(GL_LINE_LOOP, i*4, 4);
    
}

CBorder::~CBorder(){
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}