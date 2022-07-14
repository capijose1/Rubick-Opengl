#ifndef CUBITO_SHADER_H
#define CUBITO_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

class Shader {

 public:

  unsigned int id = 0;

  Shader() {}

  Shader& Use();
  void Compile(const char*, const char*);
  void SetFloat(const char*, float, bool useShader = false);
  void SetInteger(const char*, int, bool useShader = false);
  void SetVector2f(const char*, float, float, bool useShader = false);
  void SetVector2f(const char*, const glm::vec2&, bool useShader = false);
  void SetVector3f(const char*, float, float, float, bool useShader = false);
  void SetVector3f(const char*, const glm::vec3&, bool useShader = false);
  void SetVector4f(const char*, float, float, float, float, bool useShader = false);
  void SetVector4f(const char*, const glm::vec4& , bool useShader = false);
  void SetMatrix4(const char*, const glm::mat4& , bool useShader = false);
 
private:
  
  void CheckCompileErrors(unsigned int, std::string);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Shader& Shader::Use() {
  glUseProgram(this->id);
  return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource) {
  unsigned int sVertex, sFragment;
  
  // Vertex Shader
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSource, NULL);
  glCompileShader(sVertex);
  CheckCompileErrors(sVertex, "VERTEX");
  
  // Fragment Shader
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSource, NULL);
  glCompileShader(sFragment);
  CheckCompileErrors(sFragment, "FRAGMENT");
  
  // Shader program
  this->id = glCreateProgram();
  glAttachShader(this->id, sVertex);
  glAttachShader(this->id, sFragment);
  glLinkProgram(this->id);
  CheckCompileErrors(this->id, "PROGRAM");
  
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

void Shader::SetFloat(const char* name, float value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::SetInteger(const char* name, int value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::SetVector2f(const char* name, float x, float y, bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->id, name), x, y);
}

void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
  if (useShader)
    this->Use();
  glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader) {
  if (useShader)
    this->Use();
  glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader) {
  if (useShader)
    this->Use();
  glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::CheckCompileErrors(unsigned int object, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
        << infoLog << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
        << infoLog << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
}

#endif // CUBITO_SHADER_H