#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform bool      useTexture;
uniform vec3      baseColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // ── Surface color ─────────────────────────
    vec3 surfaceColor;
    if (useTexture)
        surfaceColor = texture(texture0, TexCoord).rgb;
    else
        surfaceColor = baseColor;

    // ── Ambient ───────────────────────────────
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor * surfaceColor;

    // ── Diffuse ───────────────────────────────
    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse  = diff * lightColor * surfaceColor;

    // ── Specular ──────────────────────────────
    float specularStrength = 0.6;
    vec3 viewDir    = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular   = specularStrength * spec * lightColor;

    // ── Final ─────────────────────────────────
    vec3 result = ambient + diffuse + specular;
    FragColor   = vec4(result, 1.0);
}
