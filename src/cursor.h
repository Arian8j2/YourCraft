#include "gamecontext.h"
#include "texture.h"
#include "border.h"

class CCursor{
private:
    CTexture* m_pTexture;
    CGameContext* m_pGameContext;
    CBorder* m_pBorder;

    uint32_t m_VAO;
    uint32_t m_VBO;

    uint32_t m_Program;

    glm::mat4 m_Projection;

    void Tick();

public:
    CCursor(CGameContext* pGameContext);
    ~CCursor();

    void Render();
};