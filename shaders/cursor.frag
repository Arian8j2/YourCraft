#version 330 core

in vec2 fTexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main(){
    FragColor = texture(uTexture, fTexCoord);
    
    if(FragColor.a < 0.1f)
        discard;

    FragColor.a = 0.8f;
}