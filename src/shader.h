#include "gamecontext.h"

#define SHADER_PATH "shaders"

class CShader{
private:
    uint32_t m_Value;
    

public:
    CShader(const char* pFilename, int Type);
    ~CShader();

    uint32_t GetValue() const { return m_Value; }
};