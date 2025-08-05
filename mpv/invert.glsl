//!HOOK MAIN
//!BIND HOOKED

vec4 hook() {
    vec2 pixel_pos = vec2(HOOKED_pos*HOOKED_size);
    vec4 color = HOOKED_tex(HOOKED_pos);

    color.rgb = 1.0 - color.rgb;

    return color;
}
