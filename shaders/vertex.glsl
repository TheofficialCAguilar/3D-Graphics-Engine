#version 330 core

// Input vertex attributes
layout (location = 0) in vec3 aPos;      // world position
layout (location = 1) in vec3 aNormal;   // surface normal
layout (location = 2) in vec2 aTexCoord; // UV coordinate

// Output to fragment shader
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

// Transformation matrices (set by Camera)
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // World-space position for lighting calculations
    FragPos   = vec3(model * vec4(aPos, 1.0));

    // Transform normal into world space
    // (using transpose of inverse to handle non-uniform scaling)
    Normal    = mat3(transpose(inverse(model))) * aNormal;

    // Pass UV straight through
    TexCoord  = aTexCoord;

    // Final clip-space position
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
