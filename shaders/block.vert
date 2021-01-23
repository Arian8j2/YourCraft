#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 uBlockPos;
out vec3 fColor;
out vec2 fTexCoord;

void main(){
    gl_Position = uBlockPos * vec4(vPos, 1.0f);
    fColor = vColor;
    fTexCoord = vTexCoord;
}