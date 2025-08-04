#version 330
in vec2 fragTexCoord;
out vec4 finalColor;
uniform sampler2D texture0;
uniform vec2 center;
uniform float time;
uniform float intensity;

void main() {
    vec2 texCoord = fragTexCoord;
    float dist = distance(texCoord, center);
    float wave = sin(20.0 * dist - time * 10.0) * 0.005 * intensity;
    texCoord += normalize(texCoord - center) * wave;
    finalColor = texture(texture0, texCoord);
}