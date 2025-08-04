#version 330
in vec2 fragTexCoord;
out vec4 finalColor;
uniform sampler2D texture0;
uniform float time;
uniform float frequency;
uniform float amplitude;

void main() {
    vec2 uv = fragTexCoord;
    uv.y += sin((uv.x + time) * frequency) * amplitude;
    finalColor = texture(texture0, uv);
}