/*
 * @file Shader.hpp
 * @name Carlos Aguilar
 * @brief Loads, compiles, and links GLSL vertex + fragment shaders.
 *        Provides helpers to set uniforms (mat4, vec3, int, float).
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint ID;  // program handle

    /**
     * @param vertexPath:   Path to the .glsl vertex shader file.
     * @param fragmentPath: Path to the .glsl fragment shader file.
     * @post: Compiles and links the shader program. Prints errors to stderr.
     */
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    /** @post: Binds this shader program for rendering. */
    void use() const;

    // ── Uniform setters ───────────────────────
    void setBool (const std::string& name, bool value)        const;
    void setInt  (const std::string& name, int value)         const;
    void setFloat(const std::string& name, float value)       const;
    void setVec3 (const std::string& name, float x, float y, float z) const;
    void setMat4 (const std::string& name, const float* mat)  const;

private:
    void checkCompileErrors(GLuint shader, const std::string& type) const;
};

#endif
