#version 330 core

in vec2 fTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uTextColor;

void main(){
    FragColor = uTextColor * vec4(1.0f, 1.0f, 1.0f, texture(uTexture, fTexCoord).r);
}