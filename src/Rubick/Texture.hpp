#ifndef CUBITO_TEXTURE_HPP
#define CUBITO_TEXTURE_HPP

#include <glad/glad.h>

#include <iostream>

class Texture {

public:

  Texture();

  unsigned int id;
  unsigned int width, height;
  unsigned int internal_format;
  unsigned int image_format;
  unsigned int wrap_s;
  unsigned int wrap_t;
  unsigned int filter_min;
  unsigned int filter_max;

  void Bind() const;
  void Generate(unsigned int, unsigned int, unsigned char*);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Texture::Texture() : width(0), 
  height(0), 
  internal_format(GL_RGB), 
  image_format(GL_RGB), 
  wrap_s(GL_REPEAT), 
  wrap_t(GL_REPEAT), 
  filter_min(GL_LINEAR), 
  filter_max(GL_LINEAR) {
    glGenTextures(1, &this->id);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    this->width = width;
    this->height = height;
    
    glBindTexture(GL_TEXTURE_2D, this->id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
    
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, 
    this->image_format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

#endif // CUBITO_TEXTURE_HPP