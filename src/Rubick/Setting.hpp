#ifndef CUBITO_SETTING_HPP
#define CUBITO_SETTING_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Size of screen
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

// General const variables
const double PI = 3.14159;
const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 ORANGE = glm::vec3(1.0f, 0.5f, 0.0f);
const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);

// General functions
float deg(float num) { // warning posible loss of data
  return (static_cast<float>(num * PI / 180));
}

void PrintCommands() {

  std::cout << "\t+----------------------------------------------+\n";
  std::cout << "\t|               Controles                      |\n";
  std::cout << "\t+----------------------------------------------+\n";
  std::cout << "\t|   U: U                                       |\n";
  std::cout << "\t|   Shift + U: U'                              |\n";
  std::cout << "\t|   D: D                                       |\n";
  std::cout << "\t|   Shift + D: D'                              |\n";
  std::cout << "\t|   R: R                                       |\n";
  std::cout << "\t|   Shift + R: R'                              |\n";
  std::cout << "\t|   L: L                                       |\n";
  std::cout << "\t|   Shift + L: L'                              |\n";
  std::cout << "\t|   F: F                                       |\n";
  std::cout << "\t|   Shift + F: F'                              |\n";
  std::cout << "\t|   B: B                                       |\n";
  std::cout << "\t|   Shift + B: B'                              |\n";

  std::cout << "\t+----------------------------------------------+\n";
  std::cout << "\t|              Soluciones                      |\n";
  std::cout << "\t+----------------------------------------------+\n";
  std::cout << "\t|   Random movements: Z                        |\n";
  std::cout << "\t|   Solve rubick-cube: X                       |\n";
  std::cout << "\t+----------------------------------------------+" << std::endl;
}

// Main object that control game

// Thing of camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f)); // initial position of camera
float lastX = 500.0f;
float lastY = 500.0f;
bool first_time_mouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool auto_camera = false;
float cam_y = -4.0f;
bool up_down_camera = true;


enum class Move {
  L, LP,
  R, RP,
  U, UP,
  D, DP,
  F, FP,
  B, BP
};

// Const variables of rubick_cube
const float distance_b_cubes = 0.4f;

const float angles_upper_limit[9] = {
  225.0f,
  180.0f,
  135.0f,
  270.0f,
  0.0f,
  90.0f,
  315.0f,
  360.0f,
  405.0f,
};
const float angles_lower_limit[9] = {
  45.0f,
  0.0f,
  -45.0f,
  90.0f,
  0.0f,
  -90.0f,
  135.0f,
  180.0f,
  225.0f,
};

const int kAroundXLeft = 1;
const int kAroundXRight = -1;
const int kAroundYLeft = -2;
const int kAroundYRight = 2;
const int kAroundZLeft = 3;
const int kAroundZRight = -3;

// special efect

float velocity_cubito = 1.0f;
float far_of_cubito = 1.0f;
bool efect_far_velocity = true;

#endif // CUBITO_SETTING_HPP
