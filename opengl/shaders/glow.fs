#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec3 targetColor;
uniform float boostFactor;

void main()
{
    vec4 originalColor = texture(texture0, fragTexCoord);
    
    float distance = distance(originalColor.rgb, targetColor);
    
    if (distance < 0.6)
    {
        finalColor = vec4(originalColor.rgb * boostFactor, originalColor.a);
    }
    else
    {
        finalColor = originalColor;
    }
}
