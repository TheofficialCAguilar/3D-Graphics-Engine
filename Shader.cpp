// Carlos Aguilar

#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertCode, fragCode;
    std::ifstream vFile(vertexPath), fFile(fragmentPath);

    if (!vFile.is_open() || !fFile.is_open()) {
        std::cerr << "Shader: could not open shader files\n"
                  << "  vert: " << vertexPath   << "\n"
                  << "  frag: " << fragmentPath << "\n";
        ID = 0;
        return;
    }

    std::stringstream vss, fss;
    vss << vFile.rdbuf();
    fss << fFile.rdbuf();
    vertCode = vss.str();
    fragCode = fss.str();

    const char* vSrc = vertCode.c_str();
    const char* fSrc = fragCode.c_str();

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vSrc, nullptr);
    glCompileShader(vert);
    checkCompileErrors(vert, "VERTEX");

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fSrc, nullptr);
    glCompileShader(frag);
    checkCompileErrors(frag, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vert);
    glAttachShader(ID, frag);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::use() const { glUseProgram(ID); }

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
void Shader::setMat4(const std::string& name, const float* mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat);
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) const
{
    GLint success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader compile error [" << type << "]:\n" << infoLog << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Shader link error:\n" << infoLog << "\n";
        }
    }
}
