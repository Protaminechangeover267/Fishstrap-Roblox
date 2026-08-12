// Fishstrap Shader: Vaporwave - Aesthetic 80s/90s effect
#define PINK vec3(1.0, 0.2, 0.6)
#define CYAN vec3(0.2, 0.8, 1.0)
#define PURPLE vec3(0.5, 0.1, 0.8)
#define SCANLINE_INTENSITY 0.04

vec4 vaporwave_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 c = texture(tex, uv);

    // Pink and cyan color shift
    float gray = dot(c.rgb, vec3(0.299, 0.587, 0.114));
    vec3 vaporColor = mix(PINK, CYAN, gray);
    c.rgb = mix(c.rgb, vaporColor * gray, 0.4);

    // Purple tint in shadows
    c.rgb = mix(c.rgb * PURPLE, c.rgb, smoothstep(0.0, 0.5, gray));

    // Scanlines
    float scanline = sin(uv.y * 1080.0 * 3.14159) * SCANLINE_INTENSITY;
    c.rgb -= scanline;

    // Chromatic aberration
    c.r = texture(tex, uv + vec2(0.002, 0.0)).r;
    c.b = texture(tex, uv - vec2(0.002, 0.0)).b;

    return clamp(c, 0.0, 1.0);
}
