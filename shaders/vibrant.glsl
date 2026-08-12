// Fishstrap Shader: Vibrant - Boosted color saturation
#define SATURATION 1.6
#define VIBRANCE 0.35
#define CONTRAST 1.1

vec4 vibrant_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 c = texture(tex, uv);
    float gray = dot(c.rgb, vec3(0.299, 0.587, 0.114));

    // Saturation boost
    c.rgb = mix(vec3(gray), c.rgb, SATURATION);

    // Vibrance - selective saturation (affects less-saturated colors more)
    float mx = max(c.r, max(c.g, c.b));
    float mn = min(c.r, min(c.g, c.b));
    float sat = mx - mn;
    c.rgb = mix(vec3(gray), c.rgb, 1.0 + VIBRANCE * (1.0 - sat));

    // Contrast
    c.rgb = (c.rgb - 0.5) * CONTRAST + 0.5;

    return clamp(c, 0.0, 1.0);
}
