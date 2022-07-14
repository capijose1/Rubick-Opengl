#ifndef CUBITO_CUBO_HPP
#define CUBITO_CUBO_HPP

#include <vector>
#include <memory>

#include "Cubito.hpp"
#include "Shader.h"
#include "Rendered.hpp"
using namespace std;
using namespace glm;
class Cubo {

 public:
	
	Cubo();

	vector<std::shared_ptr<Cubito>> cubitos;
	void Draw(const Rendered&, const mat4&, const mat4&, const mat4&,vec3, const unsigned int&, const unsigned int&, bool);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Cubo::Cubo() {
	cubitos.resize(28);
}

void Cubo::Draw(const Rendered& rendered, 
	const mat4& model,
	const mat4& view,
	const mat4& projection,
	vec3 camera_position,
	const unsigned int &mapa_adicional,
	const unsigned int &cube_map_ocean,
	bool background) {
	for (int i = 1; i <= 27; ++i)
		this->cubitos[i]->Draw(rendered, model, view, projection,camera_position, mapa_adicional, cube_map_ocean, background);
}

#endif // CUBITO_CUBO_HPP
