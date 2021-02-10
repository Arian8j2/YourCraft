#include "gamecontext.h"

class CBorder{
private:
    uint32_t m_VAO, m_VBO;

    CGameContext* m_pGameContext;

public:
    CBorder(CGameContext* pGameContext);
    ~CBorder();

    void Render(glm::vec3& Pos);
};