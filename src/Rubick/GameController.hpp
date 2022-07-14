#ifndef CUBITO_GAME_CONTROLLER_HPP
#define CUBITO_GAME_CONTROLLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <tuple>
#include <sstream>
#include <vector>
#include <string>

#include "Rendered.hpp"
#include "Resources.hpp"
#include "Setting.hpp"
#include "World.hpp"

class GameController {

 public:

  // COntructor and destructor
  GameController(unsigned int, unsigned int);
  ~GameController();

  // Things on game
  Rendered* Renderer = nullptr;
  Cubo rubick_cube;
  World* world;

  // General variables of game_controller
  unsigned int width = 0;
  unsigned int height = 0;
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> pos_ini;
  vector<vec3> pos_inicio_vec;
  //Variables para controlar la presión de otras
  bool can_press = true;
  bool some_movement = false;
  bool piso = false;
  bool respirar = false;
  bool keys_press[1024] {false};
  bool keys_already_press[1024] {false};
  bool inicio = true;
  //Variables para las rotaciones
  bool U_ANIM = false, U_ANIM_I = false;
  bool U_PRIME_ANIM = false, U_PRIME_ANIM_I = false;
  bool D_ANIM = false, D_ANIM_I = false;
  bool D_PRIME_ANIM = false, D_PRIME_ANIM_I = false;
  bool L_PRIME_ANIM = false, L_PRIME_ANIM_I = false;
  bool L_ANIM = false, L_ANIM_I = false;
  bool R_ANIM = false, R_ANIM_I = false;
  bool R_PRIME_ANIM = false, R_PRIME_ANIM_I = false;
  bool F_ANIM = false, F_ANIM_I = false;
  bool F_PRIME_ANIM = false, F_PRIME_ANIM_I = false;
  bool B_ANIM = false, B_ANIM_I = false;
  bool B_PRIME_ANIM = false, B_PRIME_ANIM_I = false;
  bool N_ANIM = false;
  bool expand_contract_efect = false;
  float move_angles[9] = {
    135.0f,
    90.0f,
    45.0f,
    180.0f,
    0.0f,
    0.0f,
    225.0f,
    270.0f,
    315.0f,
  };

  // Expand variables
  bool is_expanding = true;
  float kRadioLarge = 0.0f;
  float kRadioNormal = 0.0f;

  // variables solver
  std::map<Move, std::string> move_to_string;
  std::map<std::string, Move> string_to_move;
  std::map<Move, bool*> move_to_anim;
  std::map<Move, bool*> move_to_anim_i;

  std::string str_scramble;
  std::string str_solution;
  std::vector<Move> scramble;
  std::vector<Move> solution;
  int idx_scramble = 0, idx_solution = 0;

  bool shuffle_anim = false, solution_anim = false;

  // reflect
  unsigned int cube_map_night = -1;
  unsigned int cube_map_ocean = -1;
  
  // Functions of game
  void Init();
  void Render();
  void ResetAngles();
  void PlayAnimation();
  void pos_inicial();
  void Respirar(float);
  void Piso(float);
  void ChangeFragCubito();
  void UpdateGame(float,float=0); 
  void ProcessInput(float);
  void UpdateMatrices(glm::mat4, glm::mat4, glm::mat4);
  glm::vec3 CalculateTranslatePosition(float, Move, const float&);
  unsigned int loadCubemap(std::vector<std::string>);

  void StartParser();
  std::string GenScramble(int);
  std::vector<Move> ParseOutput(std::string);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

GameController::GameController(unsigned int width, unsigned int height)
  : keys_press(), 
  keys_already_press(), 
  width(width), 
  height(height) { 
}

GameController::~GameController() {
  delete Renderer;
  delete world;
}


void GameController::Init() {
  
  // Loading programs
  Resources::LoadShader("C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito_mirrow.vs", "C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito_mirrow.fs", nullptr, "cubito_mirrow");
  Resources::LoadShader("C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito_transparent.vs", "C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito_transparent.fs", nullptr, "cubito_transparent");
  Resources::LoadShader("C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito.vs", "C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/cubito.fs", nullptr, "cubito");
  Resources::LoadShader("C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/skybox.vs", "C:/Users/capijose/Documents/Rubik/src/Rubick/src/shaders/skybox.fs", nullptr, "skybox");
  
  // Loading textures
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/negro.png", true, "negro");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/amarillo.png", true, "yellow");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red.png", true, "red");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white.png", true, "white");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue.png", true, "blue");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/naranja.png", true, "orange");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green.png", true, "green");
  
  //Texturas personalizadas
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/1.png", true, "yellow1");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/2.png", true, "yellow2");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/3.png", true, "yellow3");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/4.png", true, "yellow4");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/5.png", true, "yellow5");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/6.png", true, "yellow6");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/7.png", true, "yellow7");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/8.png", true, "yellow8");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/yellow/9.png", true, "yellow9");

  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/1.png", true, "red1");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/2.png", true, "red2");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/3.png", true, "red3");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/4.png", true, "red4");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/5.png", true, "red5");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/6.png", true, "red6");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/7.png", true, "red7");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/8.png", true, "red8");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/red/9.png", true, "red9");


  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/1.png", true, "green1");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/2.png", true, "green2");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/3.png", true, "green3");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/4.png", true, "green4");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/5.png", true, "green5");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/6.png", true, "green6");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/7.png", true, "green7");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/8.png", true, "green8");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/green/9.png", true, "green9");

  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/1.png", true, "blue1");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/2.png", true, "blue2");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/3.png", true, "blue3");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/4.png", true, "blue4");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/5.png", true, "blue5");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/6.png", true, "blue6");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/7.png", true, "blue7");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/8.png", true, "blue8");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/blue/9.png", true, "blue9");

  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/1.png", true, "white1");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/2.png", true, "white2");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/3.png", true, "white3");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/4.png", true, "white4");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/5.png", true, "white5");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/6.png", true, "white6");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/7.png", true, "white7");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/8.png", true, "white8");
  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/white/9.png", true, "white9");

  Resources::LoadTexture("C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/background.jpg", false, "background");




  std::vector<std::string> ocean{
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/right.jpg",
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/left.jpg",
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/top.jpg",
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/bottom.jpg",
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/front.jpg",
  "C:/Users/capijose/Documents/Rubik/src/Rubick/src/images/back.jpg"
  };

  cube_map_ocean = loadCubemap(ocean);

  // Assing textures integers
  Resources::GetShader("cubito").Use().SetInteger("main_image_texture", 0);
  Resources::GetShader("cubito").Use().SetInteger("background_texture", 1);




  // Create main Rendered
  this->Renderer = new Rendered(Resources::GetShader("cubito"));


  // set angle rotation
  this->kRadioLarge = static_cast<float>(distance_b_cubes * sqrt(2));
  this->kRadioNormal = distance_b_cubes;
  
  // Fill input_color variable
  std::vector<glm::vec3> input_colors;
  fill_n(back_inserter(input_colors), 9, BLUE);
  for (int i = 0; i < 3; ++i) {
    fill_n(back_inserter(input_colors), 3, ORANGE);
    fill_n(back_inserter(input_colors), 3, WHITE);
    fill_n(back_inserter(input_colors), 3, RED);
    fill_n(back_inserter(input_colors), 3, YELLOW);
  }
  fill_n(back_inserter(input_colors), 9, GREEN);


  // World
  world = new World( Resources::GetShader("skybox"), 998, cube_map_night, cube_map_ocean);
  // Creating cubitos inside rubick_cube
  
      //Cubo amarillo afuera esquina superior derecha

      this->rubick_cube.cubitos[3] = std::make_shared<Cubito>(
          Resources::GetTexture("red1"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow3"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white3"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, distance_b_cubes, -distance_b_cubes), 1);
     
      //Rojo medio arriba
      this->rubick_cube.cubitos[6] = std::make_shared<Cubito>(
          Resources::GetTexture("red2"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white2"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, distance_b_cubes, -distance_b_cubes), 1);
      //rojo esquina superior izquierda
      this->rubick_cube.cubitos[9] = std::make_shared<Cubito>(
          Resources::GetTexture("red1"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green3"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white1"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, distance_b_cubes, -distance_b_cubes), 1);
      //Rojo medio derecha
      this->rubick_cube.cubitos[12] = std::make_shared<Cubito>(
          Resources::GetTexture("red6"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow6"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, 0.0f, -distance_b_cubes), 1);
      //Rojo Centro
      this->rubick_cube.cubitos[15] = std::make_shared<Cubito>(
          Resources::GetTexture("red5"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, 0.0f, -distance_b_cubes), 15,
          input_colors[31]);
      //verde medio izquierda rojo derecha
      this->rubick_cube.cubitos[18] = std::make_shared<Cubito>(
          Resources::GetTexture("red4"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green6"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, 0.0f, -distance_b_cubes), 1);
      //esquina inferior derecha rojo
      this->rubick_cube.cubitos[21] = std::make_shared<Cubito>(
          Resources::GetTexture("red9"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow9"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, -distance_b_cubes, -distance_b_cubes), 1);
      //red abajo medio
      this->rubick_cube.cubitos[24] = std::make_shared<Cubito>(
          Resources::GetTexture("red8"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, -distance_b_cubes, -distance_b_cubes), 1);
      //red abajo izquierda
      this->rubick_cube.cubitos[27] = std::make_shared<Cubito>(
          Resources::GetTexture("red7"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green9"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, -distance_b_cubes, -distance_b_cubes), 1);
      //amarillo medio arriba
      this->rubick_cube.cubitos[2] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow2"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("white6"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, distance_b_cubes, 0.0f), 1);
      //blanco medio
      this->rubick_cube.cubitos[5] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white5"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, distance_b_cubes, 0.0f), 5,
          input_colors[4]);
      //verde medio arriba y blanco
      this->rubick_cube.cubitos[8] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green2"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white4"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, distance_b_cubes, 0.0f), 1);
      //Amarillo medio 
      this->rubick_cube.cubitos[11] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow5"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, 0.0f, 0.0f), 1);
      //cubo medio no se usa
      this->rubick_cube.cubitos[14] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, 0.0f, 0.0f), 14);
      //verde medio 
      this->rubick_cube.cubitos[17] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green5"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, 0.0f, 0.0f), 1);
      //Amarillo medio abajo y naranja
      this->rubick_cube.cubitos[20] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("yellow8"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, -distance_b_cubes, 0.0f),1);
      //naranja medio
      this->rubick_cube.cubitos[23] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, -distance_b_cubes, 0.0f),1);
      //verde abajo medio naranja
      this->rubick_cube.cubitos[26] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green8"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, -distance_b_cubes, 0.0f), 1);
      //azul izquierda superior
      this->rubick_cube.cubitos[1] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue1"),
          Resources::GetTexture("yellow1"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white9"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, distance_b_cubes, distance_b_cubes), 1);
      //Azul arriba medio
      this->rubick_cube.cubitos[4] = std::make_shared<Cubito>(//aqui
          Resources::GetTexture("black"),
          Resources::GetTexture("blue2"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white8"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, distance_b_cubes, distance_b_cubes), 1);
      //azul derecha superior verde blanco
      this->rubick_cube.cubitos[7] = std::make_shared<Cubito>( 
          Resources::GetTexture("black"),
          Resources::GetTexture("blue3"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green1"),
          Resources::GetTexture("black"),
          Resources::GetTexture("white7"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, distance_b_cubes, distance_b_cubes), 1);
      //azul izquierda medio amarillo
      this->rubick_cube.cubitos[10] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue4"),
          Resources::GetTexture("yellow4"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, 0.0f, distance_b_cubes), 1);
      //azul medio
      this->rubick_cube.cubitos[13] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue5"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, 0.0f, distance_b_cubes), 1);
      //azul medio verde
      this->rubick_cube.cubitos[16] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue6"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green4"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, 0.0f, distance_b_cubes), 1);
      //azul izquierda abajo naranja
      this->rubick_cube.cubitos[19] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue7"),
          Resources::GetTexture("yellow7"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(-distance_b_cubes, -distance_b_cubes, distance_b_cubes), 1);
      //azul medio naranja
      this->rubick_cube.cubitos[22] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue8"),
          Resources::GetTexture("black"),
          Resources::GetTexture("black"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(0.0f, -distance_b_cubes, distance_b_cubes), 1);
      //azul derecha abajo naranja verde
      this->rubick_cube.cubitos[25] = std::make_shared<Cubito>(
          Resources::GetTexture("black"),
          Resources::GetTexture("blue9"),
          Resources::GetTexture("black"),
          Resources::GetTexture("green7"),
          Resources::GetTexture("orange"),
          Resources::GetTexture("black"),
          Resources::GetShader("cubito"),
          glm::vec3(distance_b_cubes, -distance_b_cubes, distance_b_cubes), 1);
  
}

void GameController::ProcessInput(float delta_time) {
    if (( this->keys_press[GLFW_KEY_RIGHT_SHIFT] && !this->keys_already_press[GLFW_KEY_RIGHT_SHIFT]) ||
      (this->keys_press[GLFW_KEY_LEFT_SHIFT] && !this->keys_already_press[GLFW_KEY_LEFT_SHIFT])) {
      
        if (this->keys_press[GLFW_KEY_U] && !this->keys_already_press[GLFW_KEY_U])
        {
          U_PRIME_ANIM = true;
          U_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_U] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_D] && !this->keys_already_press[GLFW_KEY_D])
        {
          D_PRIME_ANIM = true;
          D_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_D] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_R] && !this->keys_already_press[GLFW_KEY_R])
        {
          R_ANIM = true;
          R_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_R] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
        
        if (this->keys_press[GLFW_KEY_L] && !this->keys_already_press[GLFW_KEY_L])
        {
          L_PRIME_ANIM = true;
          L_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_L] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_F] && !this->keys_already_press[GLFW_KEY_F])
        {
          F_PRIME_ANIM = true;
          F_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_F] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
      
        if (this->keys_press[GLFW_KEY_B] && !this->keys_already_press[GLFW_KEY_B])
        {
          B_ANIM = true;
          B_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_B] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
    }
    else {
      if (this->keys_press[GLFW_KEY_U] && !this->keys_already_press[GLFW_KEY_U])
      {
        U_ANIM = true;
        U_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_U] = true;
      }

      if (this->keys_press[GLFW_KEY_D] && !this->keys_already_press[GLFW_KEY_D])
      {
        D_ANIM = true;
        D_ANIM_I = true;
        this->some_movement = true;
        this->can_press = false;
        this->keys_already_press[GLFW_KEY_D] = true;
      }

      if (this->keys_press[GLFW_KEY_R] && !this->keys_already_press[GLFW_KEY_R])
      {
        R_PRIME_ANIM = true;
        R_PRIME_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_R] = true;
      }
      
      if (this->keys_press[GLFW_KEY_L] && !this->keys_already_press[GLFW_KEY_L])
      {
        L_ANIM = true;
        L_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_L] = true;
      }
      
      if (this->keys_press[GLFW_KEY_F] && !this->keys_already_press[GLFW_KEY_F])
      {
        F_ANIM = true;
        F_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_F] = true;
      }
     
      if (this->keys_press[GLFW_KEY_B] && !this->keys_already_press[GLFW_KEY_B])
      {
        B_PRIME_ANIM = true;
        B_PRIME_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_B] = true;
      }
    }
}

void GameController::Render() {
  // Render rubick_cube
    
    rubick_cube.Draw(*Renderer,this->model,this->view,this->projection,camera.Position,this->cube_map_night,this->cube_map_ocean,  this->world->swith_background);
    this->world->Draw(this->model, this->view, this->projection, camera.GetViewMatrix());

}

void GameController::ResetAngles() {
  this->move_angles[0] = 135.0f;
  this->move_angles[1] = 90.0f;
  this->move_angles[2] = 45.0f;
  this->move_angles[3] = 180.0f;
  this->move_angles[4] = 0.0f;
  this->move_angles[5] = 0.0f;
  this->move_angles[6] = 225.0f;
  this->move_angles[7] = 270.0f;
  this->move_angles[8] = 315.0f;
}
void GameController::pos_inicial() {
    for (int i = 1; i < this->rubick_cube.cubitos.size(); i++)
        pos_ini.push_back(this->rubick_cube.cubitos[i]);
    for (int i = 0; i < this->pos_ini.size(); i++) {
        pos_inicio_vec.push_back(pos_ini[i].get()->posicion_original());
    }
}
void GameController::UpdateGame(float delta_time,float time) {

  if (this->some_movement) {
      
    this->PlayAnimation();
  }
  else if (this->respirar) {
      this->Respirar(time);
    
  }
  else if (this->piso) {
      this->Piso(time);
  }
  else {
    if (shuffle_anim) {
      if (idx_scramble == scramble.size()) {
        shuffle_anim = false;
        scramble.clear();
        idx_scramble = 0;
        return;
      }

      *(move_to_anim[scramble[idx_scramble]]) = true;
      *(move_to_anim_i[scramble[idx_scramble]]) = true;
      this->some_movement = true;
      ++idx_scramble;
    }
    else if (solution_anim) {
      if (idx_solution == solution.size()) {
        solution_anim = false;
        idx_solution = idx_scramble = 0;
        str_solution = str_scramble = "";
        solution.clear();
        return;
      }

      *(move_to_anim[solution[idx_solution]]) = true;
      *(move_to_anim_i[solution[idx_solution]]) = true;
      this->some_movement = true;
      ++idx_solution;
    }
  }
}
vec3 tmp = vec3(0.01, 0.01, 0.01);
bool coseno = 0;
void GameController::Respirar(float deltaTime) {
    std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;
    for (int i = 1; i <this->rubick_cube.cubitos.size(); i ++)
        cubitos.push_back(this->rubick_cube.cubitos[i]);
    float val1 = 0.2f;
    float val2 = -0.2f;
    bool opciones_4[4] = { -1, -1, 1, 1 };
    bool opciones_4_b[4] = { -1, 1, -1, 1 };
    int esquinas[4] = {0 };//0,6,24,18
    if (cos(deltaTime+0.1)>cos(deltaTime)) {
        coseno = 1;
    }
    if (coseno == 1) {
        if (cos(deltaTime) < 0) {
            cubitos[0].get()->SetPosition(cubitos[0].get()->posicion_original() + vec3(-0.002, 0.002, 0.002));
            cubitos[1].get()->SetPosition(cubitos[1].get()->posicion_original() + vec3(-0.002, 0.002, 0.00));
            cubitos[2].get()->SetPosition(cubitos[2].get()->posicion_original() + vec3(-0.002, 0.002, -0.002));
            cubitos[3].get()->SetPosition(cubitos[3].get()->posicion_original() + vec3(0.00, 0.002, 0.002));
            cubitos[4].get()->SetPosition(cubitos[4].get()->posicion_original() + vec3(0.00, 0.002, 0.00));
            cubitos[5].get()->SetPosition(cubitos[5].get()->posicion_original() + vec3(0.00, 0.002, -0.002));
            cubitos[6].get()->SetPosition(cubitos[6].get()->posicion_original() + vec3(0.002, 0.002, 0.002));
            cubitos[7].get()->SetPosition(cubitos[7].get()->posicion_original() + vec3(0.002, 0.002, 0.00));
            cubitos[8].get()->SetPosition(cubitos[8].get()->posicion_original() + vec3(0.002, 0.002, -0.002));
            cubitos[9].get()->SetPosition(cubitos[9].get()->posicion_original() + vec3(-0.002, 0.00, 0.002));
            cubitos[10].get()->SetPosition(cubitos[10].get()->posicion_original() + vec3(-0.002, 0.00, 0.00));
            cubitos[11].get()->SetPosition(cubitos[11].get()->posicion_original() + vec3(-0.002, 0.00, -0.002));
            cubitos[12].get()->SetPosition(cubitos[12].get()->posicion_original() + vec3(0.00, 0.00, 0.002));
            //13 es el centro
            cubitos[14].get()->SetPosition(cubitos[14].get()->posicion_original() + vec3(0.00, 0.00, -0.002));
            cubitos[15].get()->SetPosition(cubitos[15].get()->posicion_original() + vec3(0.002, 0.00, 0.002));
            cubitos[16].get()->SetPosition(cubitos[16].get()->posicion_original() + vec3(0.002, 0.00, 0.00));
            cubitos[17].get()->SetPosition(cubitos[17].get()->posicion_original() + vec3(0.002, 0.00, -0.002));
            cubitos[18].get()->SetPosition(cubitos[18].get()->posicion_original() + vec3(-0.002, -0.002, 0.002));
            cubitos[19].get()->SetPosition(cubitos[19].get()->posicion_original() + vec3(-0.002, -0.002, 0.00));
            cubitos[20].get()->SetPosition(cubitos[20].get()->posicion_original() + vec3(-0.002, -0.002, -0.002));
            cubitos[21].get()->SetPosition(cubitos[21].get()->posicion_original() + vec3(0.00, -0.002, 0.002));
            cubitos[22].get()->SetPosition(cubitos[22].get()->posicion_original() + vec3(0.00, -0.002, 0.00));
            cubitos[23].get()->SetPosition(cubitos[23].get()->posicion_original() + vec3(0.00, -0.002, -0.002));
            cubitos[24].get()->SetPosition(cubitos[24].get()->posicion_original() + vec3(0.002, -0.002, 0.002));
            cubitos[25].get()->SetPosition(cubitos[25].get()->posicion_original() + vec3(0.002, -0.002, 0.00));
            cubitos[26].get()->SetPosition(cubitos[26].get()->posicion_original() + vec3(0.002, -0.002, -0.002));
            

            for (int i = 0; i < 27; i++) {
                for (int j = 0; j < 396; j += 11) {
                    if (cubitos[i].get()->vertices_1[j] > 0) {
                        cubitos[i].get()->vertices_1[j] += 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j] -= 0.0005;
                    }
                    if (cubitos[i].get()->vertices_1[j + 1] > 0) {
                        cubitos[i].get()->vertices_1[j + 1] += 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j + 1] -= 0.0005;
                    }
                    if (cubitos[i].get()->vertices_1[j + 2] > 0) {
                        cubitos[i].get()->vertices_1[j + 2] += 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j + 2] -= 0.0005;
                    }

                }
                cubitos[i].get()->InitialRender();
            }


        }
        else {
            cubitos[0].get()->SetPosition(cubitos[0].get()->posicion_original() - vec3(-0.002, 0.002, 0.002));
            cubitos[1].get()->SetPosition(cubitos[1].get()->posicion_original() - vec3(-0.002, 0.002, 0.00));
            cubitos[2].get()->SetPosition(cubitos[2].get()->posicion_original() - vec3(-0.002, 0.002, -0.002));
            cubitos[3].get()->SetPosition(cubitos[3].get()->posicion_original() - vec3(0.00, 0.002, 0.002));
            cubitos[4].get()->SetPosition(cubitos[4].get()->posicion_original() - vec3(0.00, 0.002, 0.00));
            cubitos[5].get()->SetPosition(cubitos[5].get()->posicion_original() - vec3(0.00, 0.002, -0.002));
            cubitos[6].get()->SetPosition(cubitos[6].get()->posicion_original() - vec3(0.002, 0.002, 0.002));
            cubitos[7].get()->SetPosition(cubitos[7].get()->posicion_original() - vec3(0.002, 0.002, 0.00));
            cubitos[8].get()->SetPosition(cubitos[8].get()->posicion_original() - vec3(0.002, 0.002, -0.002));
            cubitos[9].get()->SetPosition(cubitos[9].get()->posicion_original() - vec3(-0.002, 0.00, 0.002));
            cubitos[10].get()->SetPosition(cubitos[10].get()->posicion_original() - vec3(-0.002, 0.00, 0.00));
            cubitos[11].get()->SetPosition(cubitos[11].get()->posicion_original() - vec3(-0.002, 0.00, -0.002));
            cubitos[12].get()->SetPosition(cubitos[12].get()->posicion_original() - vec3(0.00, 0.00, 0.002));
            //13 es el centro
            cubitos[14].get()->SetPosition(cubitos[14].get()->posicion_original() - vec3(0.00, 0.00, -0.002));
            cubitos[15].get()->SetPosition(cubitos[15].get()->posicion_original() - vec3(0.002, 0.00, 0.002));
            cubitos[16].get()->SetPosition(cubitos[16].get()->posicion_original() - vec3(0.002, 0.00, 0.00));
            cubitos[17].get()->SetPosition(cubitos[17].get()->posicion_original() - vec3(0.002, 0.00, -0.002));
            cubitos[18].get()->SetPosition(cubitos[18].get()->posicion_original() - vec3(-0.002, -0.002, 0.002));
            cubitos[19].get()->SetPosition(cubitos[19].get()->posicion_original() - vec3(-0.002, -0.002, 0.00));
            cubitos[20].get()->SetPosition(cubitos[20].get()->posicion_original() - vec3(-0.002, -0.002, -0.002));
            cubitos[21].get()->SetPosition(cubitos[21].get()->posicion_original() - vec3(0.00, -0.002, 0.002));
            cubitos[22].get()->SetPosition(cubitos[22].get()->posicion_original() - vec3(0.00, -0.002, 0.00));
            cubitos[23].get()->SetPosition(cubitos[23].get()->posicion_original() - vec3(0.00, -0.002, -0.002));
            cubitos[24].get()->SetPosition(cubitos[24].get()->posicion_original() - vec3(0.002, -0.002, 0.002));
            cubitos[25].get()->SetPosition(cubitos[25].get()->posicion_original() - vec3(0.002, -0.002, 0.00));
            cubitos[26].get()->SetPosition(cubitos[26].get()->posicion_original() - vec3(0.002, -0.002, -0.002));
            for (int i = 0; i < 27; i++) {
                for (int j = 0; j < 396; j += 11) {
                    if (cubitos[i].get()->vertices_1[j] > 0) {
                        cubitos[i].get()->vertices_1[j] -= 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j] += 0.0005;
                    }
                    if (cubitos[i].get()->vertices_1[j + 1] > 0) {
                        cubitos[i].get()->vertices_1[j + 1] -= 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j + 1] += 0.0005;
                    }
                    if (cubitos[i].get()->vertices_1[j + 2] > 0) {
                        cubitos[i].get()->vertices_1[j + 2] -= 0.0005;
                    }
                    else {
                        cubitos[i].get()->vertices_1[j + 2] += 0.0005;
                    }

                }
                cubitos[i].get()->InitialRender();
            }

        }
    }

    
    this->respirar = 0;
    
}

void GameController::Piso(float deltaTime) {
    std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;
    for (int i = 1; i < this->rubick_cube.cubitos.size(); i++)
        cubitos.push_back(this->rubick_cube.cubitos[i]);
    cubitos[0].get()->SetPosition(vec3(sin(deltaTime)+0.3, cos(deltaTime)-0.3, cos(deltaTime)-0.3));
    cubitos[1].get()->SetPosition(vec3(cos(deltaTime) - 1.11, cos(deltaTime) - 0.3,0));
    cubitos[2].get()->SetPosition(vec3(cos(deltaTime) -1.11, cos(deltaTime) - 0.3, sin(deltaTime)+0.3));
    cubitos[3].get()->SetPosition(vec3(-cos(deltaTime)+0.7 , -sin(deltaTime) - 0.3, -sin(deltaTime) - 0.3));
    cubitos[4].get()->SetPosition(vec3(-cos(deltaTime) * abs(cos(deltaTime))+0.5 ,cos(deltaTime)-0.3, -sin(deltaTime) - 0.7));
    cubitos[5].get()->SetPosition(vec3(-cos(deltaTime) * abs(sin(deltaTime)) + 0.5, cos(deltaTime) - 0.3, -sin(deltaTime) * cos(cos(deltaTime))-0.94));
    cubitos[6].get()->SetPosition(vec3(cos(deltaTime) - 0.3, cos(deltaTime) - 0.3, abs(cos(sin(deltaTime / 2) )) - 0.5));
    cubitos[7].get()->SetPosition(vec3(-sin(deltaTime)-0.25 , cos(deltaTime)-0.3 , sin(deltaTime)+0.7 ));
    cubitos[8].get()->SetPosition(vec3(-sin(deltaTime)-0.26, -sin(deltaTime)-0.26, sin(deltaTime)+0.3));
    cubitos[9].get()->SetPosition(vec3(sin(deltaTime)+0.3, cos(deltaTime)-0.7, -cos(deltaTime)+1.1));
    cubitos[10].get()->SetPosition(vec3(cos(deltaTime) * sin(deltaTime) + 0.15, cos(deltaTime) - 0.7, cos(deltaTime) - 0.7));
    cubitos[11].get()->SetPosition(vec3(sin(deltaTime)+0.3, cos(deltaTime)-0.7, cos(deltaTime)-1.1 ));
    cubitos[12].get()->SetPosition(vec3(sin(deltaTime)+0.7, cos(deltaTime)-0.7, sin(deltaTime)+1.1));
    cubitos[14].get()->SetPosition(vec3(0, cos(deltaTime)-0.7, cos(deltaTime)-1.1));
    cubitos[15].get()->SetPosition(vec3(sin(deltaTime)*cos(deltaTime)+0.95, cos(deltaTime)-0.7, 0.45));
    cubitos[16].get()->SetPosition(vec3(sin(deltaTime)+1.1, cos(deltaTime)-0.7, cos(deltaTime)-0.7));
    cubitos[17].get()->SetPosition(vec3(sin(deltaTime)+1.1, cos(deltaTime)-0.7,-0.4 ));
    cubitos[18].get()->SetPosition(vec3(sin(deltaTime)+0.3, -sin(deltaTime)-1.1, sin(deltaTime)+1.1));
    cubitos[19].get()->SetPosition(vec3(sin(deltaTime)+0.3, cos(deltaTime)-1.1, cos(deltaTime)-0.7));
    cubitos[20].get()->SetPosition(vec3(sin(deltaTime)+0.3 , cos(deltaTime)-1.1, cos(deltaTime)-1.1 ));
    cubitos[21].get()->SetPosition(vec3(sin(deltaTime)+0.7, cos(deltaTime)-1.1, sin(deltaTime)+1.1));
    cubitos[22].get()->SetPosition(vec3(cos(deltaTime)*cos(deltaTime)-0.5, cos(deltaTime) -1.1, sin(deltaTime)+0.7 ));
    cubitos[23].get()->SetPosition(vec3(sin(deltaTime)*sin(deltaTime)-0.5, cos(deltaTime)-1.1, cos(deltaTime)-1.1));
    cubitos[24].get()->SetPosition(vec3(sin(deltaTime)* cos(deltaTime)+0.9, cos(deltaTime)-1.1, cos(deltaTime)* sin(deltaTime)+0.9));
    cubitos[25].get()->SetPosition(vec3(sin(deltaTime) +1.1, cos(deltaTime) - 1.1, cos(deltaTime) * sin(deltaTime) + 0.4));
    cubitos[26].get()->SetPosition(vec3(sin(deltaTime)+1.1 , -cos(deltaTime)*cos(deltaTime)+0.15, cos(deltaTime)-1.1));
    if (inicio) {
        for (int i = 0; i < cubitos.size(); i++) {
            cubitos[i].get()->SetPosition(pos_inicio_vec[i]);
        }
        
        inicio = false;
    }
    if (cubitos[0].get()->posicion_original()[0]>-0.4 && cubitos[0].get()->posicion_original()[0] < -0.38 && cubitos[0].get()->posicion_original()[1]>0.4) {
        for (int i = 0; i < cubitos.size(); i++) {
            cubitos[i].get()->SetPosition(pos_inicio_vec[i]);
        }
        piso = 0;
        inicio = 1;
    }
 

}
void GameController::PlayAnimation() {
    if (this->expand_contract_efect) {

        if (this->is_expanding) {
            this->kRadioLarge += 0.1f;
            this->kRadioNormal += 0.1f;
        }
        else {
            this->kRadioLarge -= 0.1f;
            this->kRadioNormal -= 0.1f;
        }
        if (this->kRadioNormal > 1.4f) this->is_expanding = false;

    }
    else {

        this->kRadioLarge = static_cast<float>(distance_b_cubes * sqrt(2));
        this->kRadioNormal = distance_b_cubes;

    }
    std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;

    float* angles = move_angles;
    const float* angles_limit{};
    float step{}, speed = 1.0f; //velocidad
    int clockwise{};
    Move current_move{};
    int normalMove{};
 
    if (F_ANIM_I) {
        current_move = Move::F;
        clockwise = 1;
        normalMove = kAroundZLeft;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 1; i <= 25; i += 3)
            cubitos.push_back(rubick_cube.cubitos[i]);
    }
    else if (F_PRIME_ANIM_I) {
        current_move = Move::FP;
        clockwise = -1;
        normalMove = kAroundZLeft;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 1; i <= 25; i += 3)
            cubitos.push_back(rubick_cube.cubitos[i]);
    }
    else if (B_ANIM_I) {
        current_move = Move::B;
        clockwise = 1;
        normalMove = kAroundZLeft;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 3; i <= 27; i += 3)
            cubitos.push_back(rubick_cube.cubitos[i]);
    }
    else if (B_PRIME_ANIM_I) {
        current_move = Move::BP;
        clockwise = -1;
        normalMove = kAroundZLeft;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 3; i <= 27; i += 3)
            cubitos.push_back(rubick_cube.cubitos[i]);
    }
    else if (L_ANIM_I) {
        current_move = Move::L;
        clockwise = 1;
        normalMove = kAroundXRight;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 3; i <= 21; i += 9) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i - 1]);
            cubitos.push_back(rubick_cube.cubitos[i - 2]);
        }
    }
    else if (L_PRIME_ANIM_I) {
        current_move = Move::LP;
        clockwise = -1;
        normalMove = kAroundXRight;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 3; i <= 21; i += 9) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i - 1]);
            cubitos.push_back(rubick_cube.cubitos[i - 2]);
        }
    }
    else if (R_ANIM_I) {
        current_move = Move::R;
        clockwise = 1;
        normalMove = kAroundXRight;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 9; i <= 27; i += 9) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i - 1]);
            cubitos.push_back(rubick_cube.cubitos[i - 2]);
        }
    }
    else if (R_PRIME_ANIM_I) {
        current_move = Move::RP;
        clockwise = -1;
        normalMove = kAroundXRight;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 9; i <= 27; i += 9) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i - 1]);
            cubitos.push_back(rubick_cube.cubitos[i - 2]);
        }
    }
    else if (U_ANIM) {
        current_move = Move::U;
        clockwise = -1;
        normalMove = kAroundYRight;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 1; i <= 9; ++i) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i + 3]);
            cubitos.push_back(rubick_cube.cubitos[i + 6]);
        }
    }
    else if (U_PRIME_ANIM) {
        current_move = Move::UP;
        clockwise = 1;
        normalMove = kAroundYRight;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 1; i <= 9; ++i) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i + 3]);
            cubitos.push_back(rubick_cube.cubitos[i + 6]);
        }
    }
    else if (D_PRIME_ANIM) {
        current_move = Move::DP;
        clockwise = -1;
        normalMove = kAroundYRight;
        angles_limit = angles_upper_limit;
        step = speed;

        for (int i = 19; i <= 21; ++i) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i + 3]);
            cubitos.push_back(rubick_cube.cubitos[i + 6]);
        }
    }
    else if (D_ANIM) {
        current_move = Move::D;
        clockwise = 1;
        normalMove = kAroundYRight;
        angles_limit = angles_lower_limit;
        step = -speed;

        for (int i = 19; i <= 21; ++i) {
            cubitos.push_back(rubick_cube.cubitos[i]);
            cubitos.push_back(rubick_cube.cubitos[i + 3]);
            cubitos.push_back(rubick_cube.cubitos[i + 6]);
        }
    }
   
    for (int i = 1; i <= 7; i += 2) {
        if (std::abs(angles_limit[i] - angles[i]) > 0.5f) angles[i] += step;
        else {
            angles[i] = angles_limit[i];

            cubitos[i].get()->RotateAround(normalMove * clockwise, speed);
        }

        cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i], current_move, kRadioNormal));

        cubitos[i].get()->RotateAround(normalMove * -1 * clockwise, speed);
    }

    for (int i = 0; i < 8; i += 2) {
        if (i != 4) {
            if (std::abs(angles_limit[i] - angles[i]) > 0.5f) angles[i] += step;
            else {
                angles[i] = angles_limit[i];
                cubitos[i].get()->RotateAround(normalMove * clockwise, speed);
            }

            cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i], current_move, kRadioLarge));
        }

        cubitos[i].get()->RotateAround(normalMove * -1 * clockwise, speed);
    }


    if (std::abs(angles_limit[8] - angles[8]) > 0.5f) {
        angles[8] += step;
    }
    else {
        angles[8] = angles_limit[8];
        cubitos[8].get()->RotateAround(normalMove * clockwise, speed);
        cubitos[4].get()->RotateAround(normalMove * clockwise, speed);
        F_ANIM_I = false;
        B_ANIM_I = false;
        F_PRIME_ANIM_I = false;
        B_PRIME_ANIM_I = false;
        L_ANIM_I = false;
        L_PRIME_ANIM_I = false;
        R_PRIME_ANIM_I = false;
        R_ANIM_I = false;
        U_ANIM_I = false;
        U_PRIME_ANIM_I = false;
        D_ANIM_I = false;
        D_PRIME_ANIM_I = false;
        this->some_movement = false;

        // Expand contract function start
        this->is_expanding = true;
        this->kRadioLarge = static_cast<float>(distance_b_cubes * sqrt(2));
        this->kRadioNormal = distance_b_cubes;

        for (int i = 1; i <= 7; i += 2) {

            cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i], current_move, kRadioNormal));

        }
        for (int i = 0; i < 8; i += 2) {
            if (i != 4) {

                cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i], current_move, kRadioLarge));
            }
        }
        // Expand contract function end

        // Solving middle cube rotation
        cubitos[4].get()->CorrectRotate();
    }
    cubitos[8].get()->SetPosition(CalculateTranslatePosition(angles[8],current_move, kRadioLarge));

    cubitos[8].get()->RotateAround(normalMove * -1 * clockwise, speed);

    // REASIGN POINTER
    if (!this->some_movement) {
        if (clockwise > 0) {
            auto temp = cubitos[0].get();
            cubitos[0].get() = cubitos[6].get();
            cubitos[6].get() = cubitos[8].get();
            cubitos[8].get() = cubitos[2].get();
            cubitos[2].get() = temp;

            temp = cubitos[1].get();
            cubitos[1].get() = cubitos[3].get();
            cubitos[3].get() = cubitos[7].get();
            cubitos[7].get() = cubitos[5].get();
            cubitos[5].get() = temp;
        }
        else {
            auto temp = cubitos[0].get();
            cubitos[0].get() = cubitos[2].get();
            cubitos[2].get() = cubitos[8].get();
            cubitos[8].get() = cubitos[6].get();
            cubitos[6].get() = temp;

            temp = cubitos[1].get();
            cubitos[1].get() = cubitos[5].get();
            cubitos[5].get() = cubitos[7].get();
            cubitos[7].get() = cubitos[3].get();
            cubitos[3].get() = temp;
        }

        ResetAngles();

        B_ANIM = false;
        B_PRIME_ANIM = false;
        F_ANIM = false;
        F_PRIME_ANIM = false;
        L_PRIME_ANIM = false;
        L_ANIM = false;
        R_ANIM = false;
        R_PRIME_ANIM = false;
        U_ANIM = false;
        U_PRIME_ANIM = false;
        D_ANIM = false;
        D_PRIME_ANIM = false;
    }
    
}


void GameController::UpdateMatrices(glm::mat4 new_model, 
  glm::mat4 new_view, 
  glm::mat4 new_proyection) {
  this->model = new_model;
  this->view = new_view;
  this->projection = new_proyection;
}

glm::vec3 GameController::CalculateTranslatePosition(float angle, Move m, const float& radius) {
  switch (m) {
  case Move::F:
  case Move::FP:
    return glm::vec3(radius * cos(deg(angle)),
      radius * sin(deg(angle)),
      distance_b_cubes);
    break;

  case Move::B:
  case Move::BP:
    return glm::vec3(radius * cos(deg(angle)),
      radius * sin(deg(angle)),
      -distance_b_cubes);
    break;

  case Move::R:
  case Move::RP:
    return glm::vec3(distance_b_cubes,
      radius * sin(deg(angle)),
      radius * cos(deg(angle)));
    break;

  case Move::L:
  case Move::LP:
    return glm::vec3(-distance_b_cubes,
      radius * sin(deg(angle)),
      radius * cos(deg(angle)));
    break;

  case Move::U:
  case Move::UP:
    return glm::vec3(radius * cos(deg(angle)),
      distance_b_cubes,
      radius * sin(deg(angle)));
    break;

  case Move::D:
  case Move::DP:
    return glm::vec3(radius * cos(deg(angle)),
      -distance_b_cubes,
      radius * sin(deg(angle)));
  }
}

void GameController::StartParser() {
  move_to_string[Move::L] = "L";
  move_to_string[Move::R] = "R";
  move_to_string[Move::U] = "U";
  move_to_string[Move::D] = "D";
  move_to_string[Move::F] = "F";
  move_to_string[Move::B] = "B";
  move_to_string[Move::LP] = "L'";
  move_to_string[Move::RP] = "R'";
  move_to_string[Move::UP] = "U'";
  move_to_string[Move::DP] = "D'";
  move_to_string[Move::FP] = "F'";
  move_to_string[Move::BP] = "B'";

  for (auto &element : move_to_string) {
    string_to_move[element.second] = element.first;
  }

  move_to_anim[Move::UP] = &U_PRIME_ANIM;
  move_to_anim_i[Move::UP] = &U_PRIME_ANIM_I;
  move_to_anim[Move::DP] = &D_PRIME_ANIM;
  move_to_anim_i[Move::DP] = &D_PRIME_ANIM_I;
  move_to_anim[Move::RP] = &R_ANIM;
  move_to_anim_i[Move::RP] = &R_ANIM_I;
  move_to_anim[Move::LP] = &L_PRIME_ANIM;
  move_to_anim_i[Move::LP] = &L_PRIME_ANIM_I;
  move_to_anim[Move::FP] = &F_PRIME_ANIM;
  move_to_anim_i[Move::FP] = &F_PRIME_ANIM_I;
  move_to_anim[Move::BP] = &B_ANIM;
  move_to_anim_i[Move::BP] = &B_ANIM_I;

  move_to_anim[Move::U] = &U_ANIM;
  move_to_anim_i[Move::U] = &U_ANIM_I;
  move_to_anim[Move::D] = &D_ANIM;
  move_to_anim_i[Move::D] = &D_ANIM_I;
  move_to_anim[Move::R] = &R_PRIME_ANIM;
  move_to_anim_i[Move::R] = &R_PRIME_ANIM_I;
  move_to_anim[Move::L] = &L_ANIM;
  move_to_anim_i[Move::L] = &L_ANIM_I;
  move_to_anim[Move::F] = &F_ANIM;
  move_to_anim_i[Move::F] = &F_ANIM_I;
  move_to_anim[Move::B] = &B_PRIME_ANIM;
  move_to_anim_i[Move::B] = &B_PRIME_ANIM_I;
}

std::string GameController::GenScramble(int count) {
  std::random_device rd;
  std::string movements;
  for (int i = 0; i < count; ++i) {
    Move current = Move(rd() % 12);
    movements += move_to_string[current] + " ";
  }
  return movements;
}

std::vector<Move> GameController::ParseOutput(std::string output) {
  std::string tmp;
  std::vector<Move> movements;
  bool two = false;
  for (int i = 0; i < output.size(); ++i) {
    if (output[i] == ' '){
      movements.push_back(string_to_move[tmp]);
      if (two)
        movements.push_back(string_to_move[tmp]);
      tmp = "";
      two = false;
    }
    else if (output[i] == '2')
      two = true;
    else
      tmp += output[i];
  }
  return movements;
}

unsigned int GameController::loadCubemap(std::vector<std::string> faces) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;

  for (unsigned int i = 0; i < faces.size(); i++) {
    unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
      stbi_image_free(data);
    }
    else {
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


void GameController::ChangeFragCubito() {
  for (int i = 1; i <= 27; ++i)
    rubick_cube.cubitos[i]->change_fragment = !(rubick_cube.cubitos[i]->change_fragment);
}


#endif // CUBITO_GAME_CONTROLLER_HPP
