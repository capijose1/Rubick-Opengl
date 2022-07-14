#ifndef CUBITO_RENDERER_HPP
#define CUBITO_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.h"
  
class Rendered {

 public:

  Rendered(const Shader &shader);
  ~Rendered();

  void DrawSprite ( int, unsigned int, Texture&, Texture&, Texture&, Texture&, 
                    glm::vec3, glm::mat4, glm::mat4, glm::mat4, glm::mat4,
    glm::vec3, unsigned int);

 private:

  Shader shader;
  unsigned int quadVAO = -1;
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Rendered::Rendered(const Shader &shader) {
    this->shader = shader;
}

Rendered::~Rendered() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Rendered::DrawSprite(int cub_id, unsigned int nquadVAO,
  Texture &texture1,
  Texture &texture2,
  Texture &texture3,
  Texture &texture4,
  glm::vec3 position,
  glm::mat4 rotate,
  glm::mat4 model,
  glm::mat4 view,
  glm::mat4 projection,
  glm::vec3 camera_position,
  unsigned int cube_map_texture) {

  this->shader.Use();

  glm::mat4 position_on_world = glm::translate(model, position);

  position_on_world = position_on_world * rotate;
  glm::mat4 mmodel = glm::mat4(1.0f);
  unsigned int model_location = glGetUniformLocation(this->shader.id, "model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(mmodel));

  unsigned int view_location = glGetUniformLocation(this->shader.id, "view");
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

  unsigned int projection_location = glGetUniformLocation(this->shader.id, "projection");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

  unsigned int camera_location = glGetUniformLocation(this->shader.id, "cameraPos");
  glUniformMatrix4fv(camera_location, 1, GL_FALSE, glm::value_ptr(camera_position));

  glBindVertexArray(nquadVAO);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

#endif // CUBITO_RENDERER_HPP
