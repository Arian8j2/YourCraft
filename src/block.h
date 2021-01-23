#include <inttypes.h>
#include <glm/glm.hpp>

struct CBlockTexture{
    uint32_t m_Top, m_Middle, m_Bottom;

    CBlockTexture(uint32_t Top, uint32_t Middle, uint32_t Bottom):
    m_Top(Top), m_Middle(Middle), m_Bottom(Bottom){

    }
};

class CBlock{
private:
    glm::mat4 m_Pos;
    uint32_t m_BlockPosUniform;

    uint32_t m_VAO;
    uint32_t m_VBO;
    
    CBlockTexture m_Textures;
    class CGameContext* m_pGameContext;

public:
    CBlock(class CGameContext* pGameContext, glm::mat4 Pos, CBlockTexture Textures);
    ~CBlock();

    void Render();
};