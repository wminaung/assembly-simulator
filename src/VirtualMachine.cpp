#include "VirtualMachine.hpp"
#include "instructions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

VirtualMachine::VirtualMachine()
    : opcodes({{"READ", READ},
               {"WRITE", WRITE},
               {"LOAD", LOAD},
               {"STORE", STORE},
               {"ADD", ADD},
               {"SUB", SUB},
               {"DIV", DIV},
               {"MUL", MUL},
               {"JUMP", JUMP},
               {"JUMPNEG", JUMPNEG},
               {"JUMPZERO", JUMPZERO},
               {"HALT", HALT}}),
      memory{0}, accumulator(0), instruction_counter(0),
      instruction_register(0), operation_code(0), operand(0) {}

VirtualMachine::~VirtualMachine() {}

void VirtualMachine::run() {
  //
  for (i16 i = 0; i < lines.size(); ++i) {
    std::cout << "Memory[" << i << "]: " << memory[i] << std::endl;
  }
  std::cout << "_____________________________" << std::endl;
  bool executing = true;
  while (executing) {
    this->instruction_register = this->memory[this->instruction_counter];
    //
    this->operation_code = instruction_register / 100;
    this->operand = instruction_register % 100;
    instruction_counter++;
    switch (operation_code) {
    case READ:
      std::cin >> memory[operand];
      // Read input and store it in memory
      break;
    case WRITE:
      std::cout << std::endl << "The result : " << memory[operand];
      // Output the value from memory
      break;
    case LOAD:
      accumulator = memory[operand];
      // Load value from memory into accumulator
      break;
    case STORE:
      memory[operand] = accumulator;
      // Store value from accumulator into memory
      break;
    case ADD:
      accumulator += memory[operand];
      // Add value from memory to accumulator
      break;
    case SUB:
      accumulator -= memory[operand];
      // Subtract value from memory from accumulator
      break;
    case DIV:
      accumulator /= memory[operand];
      // Divide accumulator by value from memory
      break;
    case MUL:
      accumulator *= memory[operand];
      // Multiply accumulator with value from memory
      break;
    case JUMP:
      instruction_counter = operand;
      // Jump to specific memory address
      break;
    case JUMPNEG:
      if (accumulator < 0) {
        instruction_counter = operand;
      }
      // Jump if accumulator is negative
      break;
    case JUMPZERO:
      if (accumulator == 0) {
        instruction_counter = operand;
      }
      // Jump if accumulator is zero
      break;
    case HALT:
      std::cout << "\nProgram is terminated!" << std::endl;
      executing = false;
      // Stop program
      break;
    default:
      std::cout << "\nUnknown operation " << instruction_register << " code "
                << operation_code << " operand " << operand << std::endl;
      // Unknown operation
      break;
    }

    // printMemory(memory, instruction_counter, accumulator);
  }
}

VirtualMachine &VirtualMachine::readFile(std::ifstream &MyReadFile) {
  std::string line;
  while (getline(MyReadFile, line)) {
    lines.push_back(line);
  }
  MyReadFile.close();
  return *this;
}

void VirtualMachine::loadProgram() {

  for (size_t i = 0; i < lines.size(); i++) {
    std::string command;
    i16 value;
    std::stringstream ss(lines[i]);
    ss >> command >> value; // eg: "LOAD" 01
    transform(command.begin(), command.end(), command.begin(),
              ::toupper); // do uppercase
    i16 op_c = opcodes[command];
    if (op_c) {
      this->memory[i] = COMBINE(op_c, value);
    } else {
      this->memory[i] = COMBINE(JUMP, i + 1); // if empty line jump next memory
    }

    if (i == lines.size() - 1) {
      for (size_t i = 0; i < lines.size(); i++) {
        std::cout << "Memory[" << i << "]: " << memory[i] << std::endl;
      }
      std::cout << "Program loaded successfully" << std::endl;
      std::cout << "_____________________________" << std::endl;
    }
  }
}

/*
void VirtualMachine::loadProgram(std::ifstream &MyReadFile, std::string myText)
{ int i = 0;

  while (getline(MyReadFile, myText)) {
    std::string command;
    int value;
    std::stringstream ss(myText);
    ss >> command >> value; // eg: "LOAD" 01
    transform(command.begin(), command.end(), command.begin(),
              ::toupper); // do uppercase
    std::cout << command << " " << value << std::endl;
    int op_c = opcodes[command];
    if (op_c) {
      memory[i] = COMBINE(op_c, value);
      i++;
    }

    // command
  }
  MyReadFile.close();
}

*/