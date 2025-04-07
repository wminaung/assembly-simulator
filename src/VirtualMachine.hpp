#pragma once
#include "instructions.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
// type definitions

typedef int16_t i16;

class VirtualMachine {
public:
  // public functions
  VirtualMachine(/* args */);
  ~VirtualMachine();
  void run();
  VirtualMachine &readFile(std::ifstream &MyReadFile);
  void loadProgram();

private:
  /* data */
  i16 memory[100];
  std::vector<std::string> lines;
  i16 running = 1;
  i16 accumulator = 0;
  i16 instruction_counter = 0;
  i16 instruction_register = 0;
  i16 operation_code = 0;
  i16 operand = 0;
  std::map<std::string, int> opcodes;

  // private functions
  void fetch();
  void decode();
  void execute();
};
