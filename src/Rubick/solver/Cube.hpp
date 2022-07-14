#ifndef CUBE_H
#define CUBE_H

#include <iostream>

class Cube {

  void scramble();

 public:
  int cubies[9][6];
  std::string solution;

  Cube(bool);
  std::string printSequence(std::string);
  void moves(std::string sequence, bool save = true);
  void output();
  void R(int);
  void L(int);
  void U(int);
  void D(int);
  void F(int);
  void B(int);
};
#endif
