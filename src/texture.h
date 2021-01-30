#pragma once

#include "gamecontext.h"

#define TEXTURE_PATH "textures"

class CTexture{
private:
    uint32_t m_Value;

public:
    CTexture(const char* pName, int Format = GL_RGB);
    ~CTexture();

    uint32_t GetValue() const { return m_Value; }
};