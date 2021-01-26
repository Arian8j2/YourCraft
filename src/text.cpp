#include "text.h"
#include "shader.h"

#include <ft2build.h>
#include <freetype/freetype.h>

CTextRenderer::CTextRenderer(){
    FT_Library FtLib;
    if(FT_Init_FreeType(&FtLib)){
        puts("Error, Cannot initialize Freetype");
        throw 1;
    }

    FT_Face FtFace;
    if(FT_New_Face(FtLib, FONTS_PATH "/Minecraft.ttf", 0, &FtFace)){
        fprintf(stderr, "Error, Cannot find font Minecraft.ttf in %s folder\n", FONTS_PATH);
        throw 1;
    }

    FT_Set_Pixel_Sizes(FtFace, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for(uint8_t i = PRINTABLE_CHAR_OFFSET; i < 128; i++){
        if(FT_Load_Char(FtFace, i, FT_LOAD_RENDER)){
            m_aCharacterMap[i].m_TextureID = 0;
            continue;
        }

        uint32_t Tex;
        glGenTextures(1, &Tex);
        glBindTexture(GL_TEXTURE_2D, Tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, FtFace->glyph->bitmap.width, FtFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, FtFace->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_aCharacterMap[i].m_TextureID = Tex;
        m_aCharacterMap[i].m_Size = glm::ivec2(FtFace->glyph->bitmap.width, FtFace->glyph->bitmap.rows);
        m_aCharacterMap[i].m_Bearing = glm::ivec2(FtFace->glyph->bitmap_left, FtFace->glyph->bitmap_top);
        m_aCharacterMap[i].m_Advance = (uint32_t)FtFace->glyph->advance.x;
    
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(FtFace);
    FT_Done_FreeType(FtLib);

    m_TextProgram = glCreateProgram();

    CShader VertexShader("text.vert", GL_VERTEX_SHADER);
    CShader FragShader("text.frag", GL_FRAGMENT_SHADER);

    glAttachShader(m_TextProgram, VertexShader.GetValue());
    glAttachShader(m_TextProgram, FragShader.GetValue());
    glLinkProgram(m_TextProgram);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float)*4, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float)*4, (void*)(sizeof(float)*2));
    glEnableVertexAttribArray(1);

    m_ColorUniformLoc = glGetUniformLocation(m_TextProgram, "uTextColor");
    m_ProjUniformLoc = glGetUniformLocation(m_TextProgram, "uProjection");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CTextRenderer::~CTextRenderer(){
    for(int i=PRINTABLE_CHAR_OFFSET; i < 128; i++){
        if(m_aCharacterMap[i].m_TextureID == 0)
            continue;

        glDeleteTextures(1, &m_aCharacterMap[i].m_TextureID);
    }
}

void CTextRenderer::RenderText(const char* pText, float X, float Y, float Scale, RGBAColor& Color){
    glUseProgram(m_TextProgram);

    static glm::mat4 s_Proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
    glUniformMatrix4fv(m_ProjUniformLoc, 1, 0, glm::value_ptr(s_Proj));
    glUniform4f(m_ColorUniformLoc, Color.r, Color.g, Color.b, Color.a);
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);


    for(int i=0; i < strlen(pText); i++){
        uint8_t SelectedChar = pText[i];
        if(SelectedChar < PRINTABLE_CHAR_OFFSET || SelectedChar > 128)
            continue;
        
        CCharData* pCharData = &m_aCharacterMap[SelectedChar];
        float XPos = X + pCharData->m_Bearing.x * Scale;
        float YPos = Y - (pCharData->m_Size.y - pCharData->m_Bearing.y) * Scale;

        float Width = pCharData->m_Size.x * Scale;
        float Height = pCharData->m_Size.y * Scale;

        float aVerticies[] = {
            XPos, YPos + Height,  0.0f, 0.0f,            
            XPos,          YPos,  0.0f, 1.0f,
            XPos + Width,  YPos,  1.0f, 1.0f,

            XPos, YPos + Height,  0.0f, 0.0f,
            XPos + Width,  YPos,  1.0f, 1.0f,
            XPos + Width, YPos + Height, 1.0f, 0.0f           
        };

        glBindTexture(GL_TEXTURE_2D, pCharData->m_TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(aVerticies), aVerticies);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        X += (pCharData->m_Advance >> 6) * Scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}