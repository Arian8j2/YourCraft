#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uProj;
out vec2 fTexCoord;

void main(){
    gl_Position = uProj * vec4(vPos, 0.0f, 1.0f);
    fTexCoord = vTexCoord;
}