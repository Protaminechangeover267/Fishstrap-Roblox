// Fishstrap Shader: Cartoon - Cel-shaded anime effect
#define CEL_LEVELS 5.0
#define EDGE_THRESHOLD 0.15

vec4 cartoon_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 c = texture(tex, uv);

    // Cel shading - quantize to discrete levels
    c.rgb = floor(c.rgb * CEL_LEVELS) / CEL_LEVELS;

    // Edge detection
    vec4 left = texture(tex, uv - vec2(1.0/1920.0, 0.0));
    vec4 right = texture(tex, uv + vec2(1.0/1920.0, 0.0));
    vec4 up = texture(tex, uv - vec2(0.0, 1.0/1080.0));
    vec4 down = texture(tex, uv + vec2(0.0, 1.0/1080.0));

    float edge = length(c - left) + length(c - right) +
                 length(c - up) + length(c - down);

    if (edge > EDGE_THRESHOLD) {
        c.rgb = vec3(0.0);
    }

    return c;
}
