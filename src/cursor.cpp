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

    m_pBorder = new CBorder(m_pGameContext);
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
    CPlayer* pPlayer = m_pGameContext->GetPlayer(); 
    glm::vec3 PosBuffer = pPlayer->m_Camera.m_Pos;
    glm::vec3 Dir = glm::vec3(pPlayer->m_Camera.m_Front.x/16.0f, pPlayer->m_Camera.m_Front.y/16.0f, pPlayer->m_Camera.m_Front.z/16.0f);

    static glm::vec3 s_BlockSize(0.5f, 0.5f, 0.5f);
    pPlayer->m_DoesSelected = false;

    while(CCollision::Distance(PosBuffer, pPlayer->m_Camera.m_Pos) < 4.5f){
        PosBuffer += Dir;

        for(CBlockInfo& BlockInfo: m_pGameContext->m_aBlockInfos){
            if(CCollision::InterestPoint(PosBuffer, BlockInfo.m_Pos, s_BlockSize)){
                pPlayer->m_DoesSelected = true;
                pPlayer->m_SelectedBlock = BlockInfo.m_Pos;
                m_pBorder->Render(BlockInfo.m_Pos);

                PosBuffer -= Dir;
                pPlayer->m_NewBlockPos = glm::round(PosBuffer);
                return;
            }
        }
    }
}

CCursor::~CCursor(){
    delete m_pTexture;
    delete m_pBorder;
    // glDeleteBuffers(1, &m_VBO);
    // glDeleteVertexArrays(1, &m_VAO);
    // glDeleteProgram(m_Program);
}