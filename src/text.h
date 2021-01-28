#include "gamecontext.h"

#define FONTS_PATH "fonts"
#define PRINTABLE_CHAR_OFFSET 33

class CTextRenderer{
private:
    struct CCharData{
        uint32_t m_TextureID;
        glm::ivec2 m_Size;
        glm::ivec2 m_Bearing;
        uint32_t m_Advance;
    };

    CCharData m_aCharacterMap[128]; // just ascii
    uint32_t m_TextProgram;

    uint32_t m_VAO;
    uint32_t m_VBO;

    uint32_t m_ColorUniformLoc;
    uint32_t m_ProjUniformLoc;

    class CGameContext* m_pGameContext;

public:
    CTextRenderer(class CGameContext* pGameContext);
    ~CTextRenderer();

    void RenderText(const char* pText, float X, float Y, float Scale, RGBAColor& Color);
};