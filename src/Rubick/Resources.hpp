#ifndef CUBITO_RESOURCES_HPP
#define CUBITO_RESOURCES_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#include "Texture.hpp"
#include "stb_image.h"
#include "Shader.h"

class Resources {

 public:

  static std::map<std::string, Shader> all_shaders;
  static std::map<std::string, Texture> all_textures;
    
  static void Clear();
  static Shader GetShader(std::string );
  static Texture GetTexture(std::string );
  static Texture LoadTexture(const char*, bool alpha, std::string );
  static Shader LoadShader(const char*, const char*, const char*, std::string);

private:

  Resources() {}
  static Texture loadTextureFromFile(const char*, bool );
  static Shader loadShaderFromFile(const char *, const char *, const char *gShaderFile = nullptr);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

// Singlenton global variables
std::map<std::string, Shader> Resources::all_shaders;
std::map<std::string, Texture> Resources::all_textures;

void Resources::Clear() {
    for (auto iter : all_shaders)
        glDeleteProgram(iter.second.id);
    for (auto iter : all_textures)
        glDeleteTextures(1, &iter.second.id);
}

Shader Resources::GetShader(std::string name) {
    return all_shaders[name];
}

Shader Resources::LoadShader(const char *vShaderFile,
  const char *fShaderFile,
  const char *gShaderFile,
  std::string name) {
    all_shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return all_shaders[name];
}

Shader Resources::loadShaderFromFile(const char *vShaderFile, 
  const char *fShaderFile, 
  const char *gShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        
        vertexShaderFile.close();
        fragmentShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

Texture Resources::GetTexture(std::string name) {
    return all_textures[name];
}

Texture Resources::loadTextureFromFile(const char *file, bool alpha) {
    Texture texture;
    if (alpha) {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    stbi_image_free(data);
    return texture;
}

Texture Resources::LoadTexture(const char *file, bool alpha, std::string name) {
    all_textures[name] = loadTextureFromFile(file, alpha);
    return all_textures[name];
}

#endif // CUBITO_RESOURCES_HPP