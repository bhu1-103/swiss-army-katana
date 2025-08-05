//!HOOK MAIN
//!BIND HOOKED

vec4 hook() {
    vec2 pixel_pos = vec2(HOOKED_pos*HOOKED_size);
    vec2 pixel_center = vec2(HOOKED_size.x/2,HOOKED_size.y/2);

    float dist = distance(pixel_pos,pixel_center);
    float max_dist = length(HOOKED_size/2.0);

    float vignette = smoothstep(max_dist*0.9,max_dist*0.4, dist);
    vec4 color = HOOKED_tex(HOOKED_pos);
    color.rgb = color.rgb*vignette;

    return color;
}
