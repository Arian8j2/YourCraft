#include "gamecontext.h"

#define SPEED 250

class CPlayer{
private:
    CGameContext* m_pGameContext;

    struct CMouseData{
        bool m_Left, m_Right;
    };

public:
    CPlayer(CGameContext* pGameContext);

    void UpdateView();

    void HandleInputs(float DeltaTime);
    void HandleMouseMovement(double X, double Y);

    struct CCamera{
        glm::vec3 m_Pos, m_WorldUp, m_Front, m_Up, m_Right;
    } m_Camera;

    glm::mat4 m_View;

    bool m_DoesSelected;
    glm::vec3 m_SelectedBlock;
};