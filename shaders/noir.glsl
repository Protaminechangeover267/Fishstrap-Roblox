// Fishstrap Shader: Noir - Black and white film effect
#define GRAIN_INTENSITY 0.05
#define VIGNETTE_STRENGTH 0.6

vec4 noir_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 c = texture(tex, uv);

    // Convert to grayscale with film-like weighting
    float gray = dot(c.rgb, vec3(0.299, 0.587, 0.114));
    gray = pow(gray, 1.1);

    // High contrast
    gray = (gray - 0.5) * 1.4 + 0.5;

    // Vignette
    vec2 center = uv - 0.5;
    float vig = 1.0 - dot(center, center) * VIGNETTE_STRENGTH;
    gray *= vig;

    // Film grain
    float grain = fract(sin(dot(uv * 1234.5678, vec2(12.9898, 78.233))) * 43758.5453);
    gray += (grain - 0.5) * GRAIN_INTENSITY;

    return vec4(vec3(clamp(gray, 0.0, 1.0)), c.a);
}
