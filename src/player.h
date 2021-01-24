#include "gamecontext.h"

#define MOUSE_SENSITIVITY 100

class CPlayer{
private:
    CGameContext* m_pGameContext;

public:
    CPlayer(CGameContext* pGameContext);

    void UpdateView();

    void HandleInputs();
    void HandleMouseMovement(double X, double Y);

    struct CCamera{
        glm::vec3 m_Pos, m_WorldUp, m_Front, m_Up;
    } m_Camera;

    glm::mat4 m_View;
};