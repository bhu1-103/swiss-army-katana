#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform float vignetteAmount;

void main() {
    vec2 uv = fragTexCoord;
    vec4 color = texture(texture0, uv);

    // Calculate vignette
    float dist = distance(uv, vec2(0.5, 0.5));
    color.rgb *= smoothstep(0.8, 0.2, dist * vignetteAmount);

    finalColor = color;
}