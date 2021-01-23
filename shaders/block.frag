#version 330 core

in vec3 fColor;
in vec2 fTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main(){
    FragColor = texture(uTexture, fTexCoord) * vec4(fColor, 1.0f);
}