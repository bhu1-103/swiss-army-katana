#version 330
in vec2 fragTexCoord;
out vec4 finalColor;
uniform sampler2D texture0;
void main() {
    vec4 color = texture(texture0, fragTexCoord);
    finalColor = vec4(1.0 - color.rgb, color.a);
}