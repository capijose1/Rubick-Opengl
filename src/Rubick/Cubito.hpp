#ifndef CUBITO_CUBITO_HPP
#define CUBITO_CUBITO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "Shader.h"
#include "Rendered.hpp"
using namespace glm;
using namespace std;
class Cubito {


public:
int id = -1;
Shader shader;
Shader shader2;
Shader shader3;
Texture texture1;
Texture texture2;
Texture texture3;
Texture texture4;
Texture texture5;
Texture texture6;
unsigned int quadVAO = -1;
vec3 color1 = vec3(0.1f, 0.1f, 0.1f);
vec3 color2 = vec3(0.1f, 0.1f, 0.1f);
vec3 color3 = vec3(0.1f, 0.1f, 0.1f);
mat4 rotation = mat4(1.0f);
vec3 position = vec3(0.0f, 0.0f, 0.0f);
float vertices_1[396] = {
	// position          // color          // texture  // normals
			// BACK
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f, //10
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f, //21
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

	// FRONTAL
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	// LATERAL LEFT
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

	// LATERAL RIGHT
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	 // DOWN
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	// UP
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
};
mat4 GetPositionOnWorld(mat4&);



Cubito(Texture, Texture, Texture, Texture, Texture, Texture, const Shader&, vec3, int, vec3, vec3, vec3);
Cubito() {}
~Cubito();

bool change_fragment = false;

void AllData();
void InitialRender();
void RotateAround(int around_axis, float angle);
void CorrectRotate();
vec3 posicion_original();
void SetPosition(vec3);
void Draw(const Rendered&, const mat4&, const mat4&, const mat4&, 
vec3, const unsigned int&, const unsigned int&, bool);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Cubito::Cubito (
    Texture new_texture1,
    Texture new_texture2,
    Texture new_texture3,
    Texture new_texture4,
	Texture new_texture5,
	Texture new_texture6,
    const Shader& shader,
    vec3 first_position,
    int new_id,
    vec3 color1n = vec3(0.1f, 0.1f, 0.1f),
    vec3 color2n = vec3(0.1f, 0.1f, 0.1f),
    vec3 color3n = vec3(0.1f, 0.1f, 0.1f)) :
    texture1(new_texture1),
    texture2(new_texture2),
    texture3(new_texture3),
    texture4(new_texture4),
	texture5(new_texture5),
	texture6(new_texture6),
    id(new_id),
    shader(shader),
    shader2(shader2),
    shader3(shader3),
    position(first_position),
    color1(color1n),
    color2(color2n),
    color3(color3n) {

    this->InitialRender();
}

Cubito::~Cubito() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Cubito::Draw(const Rendered &rendered,

  const mat4& model,
  const mat4& view,
  const mat4& projection,
	vec3 camera_position,
  const unsigned int &cube_map_night,
  const unsigned int &cube_map_ocean,
  bool background) {
	
  Shader shader_run = this->shader;
  Shader shader_run2 = this->shader2;
  Shader shader_run3 = this->shader3;

  if (this->change_fragment) shader_run = this->shader3;

  shader_run.Use();

  mat4 position_on_world = translate(model, position);

  position_on_world = position_on_world * rotation;
  
  unsigned int model_location = glGetUniformLocation(shader_run.id, "model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(position_on_world));

  unsigned int view_location = glGetUniformLocation(shader_run.id, "view");
  glUniformMatrix4fv(view_location, 1, GL_FALSE, value_ptr(view));

  unsigned int projection_location = glGetUniformLocation(shader_run.id, "projection");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, value_ptr(projection));

  unsigned int camera_location = glGetUniformLocation(shader_run.id, "cameraPos");
  glUniform3f(camera_location, camera_position.x,camera_position.y,camera_position.z);

  glBindVertexArray(this->quadVAO);

  if (this->change_fragment) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_ocean);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    return;
  }
  
  switch (this->id) {
  case 1: {
      glActiveTexture(GL_TEXTURE0);
      texture1.Bind();
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glActiveTexture(GL_TEXTURE0);
      texture2.Bind();
      glDrawArrays(GL_TRIANGLES, 6, 6);
      glActiveTexture(GL_TEXTURE0);
      texture3.Bind();
      glDrawArrays(GL_TRIANGLES, 12, 6);
      glActiveTexture(GL_TEXTURE0);
      texture4.Bind();
      glDrawArrays(GL_TRIANGLES, 18, 6);
      glActiveTexture(GL_TEXTURE0);
      texture5.Bind();
      glDrawArrays(GL_TRIANGLES, 24, 6);
      glActiveTexture(GL_TEXTURE0);
      texture6.Bind();
      glDrawArrays(GL_TRIANGLES, 30, 6);
      break;
  }
  default: {
	  glActiveTexture(GL_TEXTURE0);
	  texture1.Bind();
	  glDrawArrays(GL_TRIANGLES, 0, 6);
	  glActiveTexture(GL_TEXTURE0);
	  texture2.Bind();
	  glDrawArrays(GL_TRIANGLES, 6, 6);
	  glActiveTexture(GL_TEXTURE0);
	  texture3.Bind();
	  glDrawArrays(GL_TRIANGLES, 12, 6);

	  glActiveTexture(GL_TEXTURE0);
	  texture4.Bind();
	  glDrawArrays(GL_TRIANGLES, 18, 6);
	  glActiveTexture(GL_TEXTURE0);
	  texture5.Bind();
	  glDrawArrays(GL_TRIANGLES, 24, 6);
	  glActiveTexture(GL_TEXTURE0);
	  texture6.Bind();
	  glDrawArrays(GL_TRIANGLES, 30, 6);
	  break;
  }
  }
  
  
  glBindVertexArray(0);

}

mat4 Cubito::GetPositionOnWorld(mat4& model) {

	mat4 position_on_world = translate(model, position);
	
	position_on_world =  position_on_world * rotation;
	
	return  position_on_world;
}
vec3 Cubito::posicion_original() {
	return this->position;
}
void Cubito::SetPosition(vec3 new_position) {
  this->position = new_position;
}

void Cubito::RotateAround(int around_axis, float angle) {
	switch (around_axis) {
		case 1: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(angle),
				vec3(1.0f, 0.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -1: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(-angle),
				vec3(1.0f, 0.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case 2: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(-angle),
				vec3(0.0f, 1.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -2: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(angle),
				vec3(0.0f, 1.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case 3: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(angle),
				vec3(0.0f, 0.0f, 1.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -3: {
			mat4 temporal = mat4(1.0f);
			temporal = rotate(temporal,
				radians(-angle),
				vec3(0.0f, 0.0f, 1.0f));

			this->rotation = temporal * rotation;

			break;
		}
	}
}

void Cubito::CorrectRotate() {
		this->rotation = mat4(1.0f);
}

void Cubito::InitialRender() {
  unsigned int VBO;
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices_1), &this->vertices_1, GL_STATIC_DRAW);
	glBindVertexArray(this->quadVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

}

void Cubito::AllData() {
	//std::cout << " rotation: " << this->rotation << std::endl;
	std::cout << " position: " << this->position << std::endl;
}

#endif // CUBITO_CUBITO_HPP
