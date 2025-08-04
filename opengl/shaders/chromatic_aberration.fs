#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform float offset;

void main() {
    vec2 uv = fragTexCoord;

    vec4 col;
    col.r = texture(texture0, uv + vec2(offset, 0.0)).r;
    col.g = texture(texture0, uv).g;
    col.b = texture(texture0, uv - vec2(offset, 0.0)).b;

    finalColor = vec4(col.rgb, 1.0);
}
