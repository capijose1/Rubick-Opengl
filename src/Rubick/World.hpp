#ifndef CUBITO_WORLD_HPP
#define CUBITO_WORLD_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>
#include <vector>

#include "Shader.h"
#include "Rendered.hpp"

class World {

private:

	int id = -1;
	Shader shader;
	unsigned int quadVAO = -1;
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glm::mat4 GetPositionOnWorld(glm::mat4&);

public:

	World(const Shader&, int, unsigned int&, unsigned int&);
	World() {}
  ~World();

	unsigned int cube_map_night = -1;
	unsigned int cube_map_ocean = -1;
	bool swith_background = false;
	void InitialRender();
	unsigned int loadCubemap(std::vector<std::string>);
	void Draw(const glm::mat4&, glm::mat4, const glm::mat4&, glm::mat4);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

World::World(
	const Shader& shader,
	int new_id, unsigned int &new_cube_map, 
	unsigned int& new_cube_ocen) :
	shader(shader),
	cube_map_night(new_cube_map),
	cube_map_ocean(new_cube_ocen),
	id(new_id) {

	this->InitialRender();
	this->shader.Use();
	this->shader.SetInteger("skybox", 0);
}

World::~World() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void World::Draw(
	const glm::mat4& model,
	glm::mat4 view,
	const glm::mat4& projection,
	glm::mat4 look_at) {
	
	glDepthFunc(GL_LEQUAL); 
	this->shader.Use();
	view = glm::mat4(glm::mat3(look_at));
	this->shader.SetMatrix4("view", view);
	this->shader.SetMatrix4("projection", projection);
	
	glBindVertexArray(this->quadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_ocean);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);

}

void World::InitialRender() {
  unsigned int VBO;

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

unsigned int World::loadCubemap(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;

	for (unsigned int i = 0; i < faces.size(); i++)	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)	{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
				0, 
				GL_RGB,
				width, 
				height, 
				0, 
				GL_RGB,
				GL_UNSIGNED_BYTE, 
				data);
			stbi_image_free(data);
		}	else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

#endif // CUBITO_WORLD_HPP
