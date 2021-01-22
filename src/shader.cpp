#include "shader.h"

CShader::CShader(const char* pFilename, int Type){
    char aFilePath[128];
    snprintf(aFilePath, sizeof(aFilePath), "%s/%s", SHADER_PATH, pFilename);

    FILE* pFile = fopen(aFilePath, "r");
    if(!pFile){
        fprintf(stderr, "Error, Cannot find shader file called %s inside %s folder\n", pFilename, SHADER_PATH);
        throw 1;
    }

    fseek(pFile, 0, SEEK_END);
    int Size = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char* pText = new char[Size + 1];
    fread(pText, 1, Size, pFile);
    pText[Size] = '\0';
    
    fclose(pFile);
    m_Value = glCreateShader(Type);
    glShaderSource(m_Value, 1, &pText, 0);
    glCompileShader(m_Value);

    int Success = 0;
    glGetShaderiv(m_Value, GL_COMPILE_STATUS, &Success);

    if(!Success){
        int ErrSize;
        glGetShaderiv(m_Value, GL_INFO_LOG_LENGTH, &ErrSize);

        char* pBuf = new char[ErrSize];
        glGetShaderInfoLog(m_Value, ErrSize, 0, pBuf);
        fprintf(stderr, "Error, Cannot compile %s shader: \n    %s", pFilename, pBuf);

        glDeleteShader(m_Value);
        delete[] pBuf;
        throw 1;
    }

    delete[] pText;
}

CShader::~CShader(){
    glDeleteShader(m_Value);
}
