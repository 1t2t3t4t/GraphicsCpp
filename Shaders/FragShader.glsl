#version 330

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float Val;

void main() {
    vec2 flippedCoord = vec2(-TexCoord.x, TexCoord.y);
    FragColor = mix(texture(ourTexture, flippedCoord), texture(ourTexture2, TexCoord), Val);
}
