#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uBlockPos;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uColor;

out vec3 fColor;
out vec2 fTexCoord;

void main(){
    gl_Position = uProjection * uView * uBlockPos * vec4(vPos, 1.0f);
    fColor = uColor;
    fTexCoord = vTexCoord;
}