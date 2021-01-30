#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

CTexture::CTexture(const char* pName, int Format){
    char aFilePath[128];
    snprintf(aFilePath, sizeof(aFilePath), "%s/%s.png", TEXTURE_PATH, pName);

    stbi_set_flip_vertically_on_load(true);

    int Width, Height, Channels;
    void* pData = stbi_load(aFilePath, &Width, &Height, &Channels, 0);
    if(!pData){
        throw 1;
    }

    glGenTextures(1, &m_Value);
    glBindTexture(GL_TEXTURE_2D, m_Value);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, Format,  Width, Height, 0, Format, GL_UNSIGNED_BYTE, pData);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(pData);
}

CTexture::~CTexture(){
    glDeleteTextures(1, &m_Value);
}