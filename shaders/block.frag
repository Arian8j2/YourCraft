#version 330 core

in vec3 iColor;
out vec4 FragColor;

void main(){
    FragColor = vec4(iColor, 1.0f);
}