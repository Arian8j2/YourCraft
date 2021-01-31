#include "cursor.h"
#include "shader.h"
#include "player.h"

CCursor::CCursor(CGameContext* pGameContext): m_pGameContext(pGameContext){
    m_pTexture = new CTexture("cursor", GL_RGBA);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    float aVerticies[] = {
        -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(aVerticies), aVerticies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*4, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*4, (void*)(sizeof(float)*2));
    glEnableVertexAttribArray(1);

    m_Program = glCreateProgram();
    CShader VertexSh("cursor.vert", GL_VERTEX_SHADER);
    CShader FragSh("cursor.frag", GL_FRAGMENT_SHADER);

    glAttachShader(m_Program, VertexSh.GetValue());
    glAttachShader(m_Program, FragSh.GetValue());

    glLinkProgram(m_Program);

    m_Projection = glm::ortho(0.0f, (float)m_pGameContext->m_Width, (float)m_pGameContext->m_Height, 0.0f, -1.0f, 1.0f);
    
    glm::mat4 Model(1.0f);
    Model = glm::translate(Model, glm::vec3((float)m_pGameContext->m_Width/2 - 5.0f, (float)m_pGameContext->m_Height/2, 0.0f));
    Model = glm::scale(Model, glm::vec3(50.0f, 50.0f, 1.0f)); 
    
    m_Projection *= Model;
}

void CCursor::Render(){
    Tick();
    glUseProgram(m_Program);
    glUniformMatrix4fv(glGetUniformLocation(m_Program, "uProj"), 1, 0, glm::value_ptr(m_Projection));

    glBindVertexArray(m_VAO);
    glBindTexture(GL_TEXTURE_2D, m_pTexture->GetValue());
    glActiveTexture(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CCursor::Tick(){
    glm::vec3 PosBuffer = m_pGameContext->GetPlayer()->m_Camera.m_Pos;

    while(CCollision::Distance(PosBuffer, m_pGameContext->GetPlayer()->m_Camera.m_Pos) < 2.0f){
        PosBuffer += m_pGameContext->GetPlayer()->m_Camera.m_Front;

        for(CBlockInfo& BlockInfo: m_pGameContext->m_aBlockInfos){
            if(CCollision::InterestPoint(PosBuffer, BlockInfo.m_Pos, 0.4f)){
                BlockInfo.m_Type = BLOCK_DIRT;
                return;
            }
        }
    }
}

CCursor::~CCursor(){
    delete m_pTexture;
    // glDeleteBuffers(1, &m_VBO);
    // glDeleteVertexArrays(1, &m_VAO);
    // glDeleteProgram(m_Program);
}