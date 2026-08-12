// Fishstrap Shader: Custom Shader Template
// Copy this file to create your own shader
// Save as: shaders/your_shader_name.glsl

// Your custom constants here
#define MY_CONSTANT 1.0

// Main shader pass function
// Parameters:
//   color  - input pixel color
//   uv     - texture coordinates (0.0 to 1.0)
//   tex    - source texture sampler
vec4 custom_pass(vec4 color, vec2 uv, sampler2D tex) {
    vec4 c = texture(tex, uv);

    // --- YOUR SHADER CODE HERE ---

    // Example: simple brightness boost
    // c.rgb *= 1.2;

    // Example: color tint
    // c.rgb *= vec3(1.0, 0.9, 0.8); // warm tint

    // --- END YOUR CODE ---

    return clamp(c, 0.0, 1.0);
}
