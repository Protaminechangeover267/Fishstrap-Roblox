// Fishstrap Shader: Realism - Enhanced realistic lighting
// Applies to Roblox D3D11 render pipeline

// Enhanced contrast and brightness
#define CONTRAST_BOOST 1.15
#define BRIGHTNESS_BOOST 1.05

// Enhanced saturation
#define SATURATION_BOOST 1.25

// Ambient occlusion approximation
#define AO_RADIUS 0.5
#define AO_INTENSITY 0.8

vec4 realism_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 original = texture(tex, uv);

    // Contrast
    float gray = dot(original.rgb, vec3(0.299, 0.587, 0.114));
    original.rgb = mix(vec3(gray), original.rgb, CONTRAST_BOOST);

    // Brightness
    original.rgb *= BRIGHTNESS_BOOST;

    // Saturation
    float lum = dot(original.rgb, vec3(0.299, 0.587, 0.114));
    original.rgb = mix(vec3(lum), original.rgb, SATURATION_BOOST);

    // Tone mapping (ACES approximation)
    original.rgb = (original.rgb * (2.51 * original.rgb + 0.03)) /
                   (original.rgb * (2.43 * original.rgb + 0.59) + 0.14);

    return vec4(clamp(original.rgb, 0.0, 1.0), original.a);
}
