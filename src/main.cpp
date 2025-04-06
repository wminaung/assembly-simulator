#include "instructions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define COMBINE(op, addr) ((op)*100 + (addr))
using namespace std;

int main() {
  ifstream MyReadFile("myasm.asm");
  string myText = "";
  //
  map<string, int> opcodes = {
      {"READ", READ},       {"WRITE", WRITE},       {"LOAD", LOAD},
      {"STORE", STORE},     {"ADD", ADD},           {"SUB", SUB},
      {"DIV", DIV},         {"MUL", MUL},           {"JUMP", JUMP},
      {"JUMPNEG", JUMPNEG}, {"JUMPZERO", JUMPZERO}, {"HALT", HALT}};

  //
  int memory[100] = {0};
  int accumulator = 0;
  int instruction_counter = 0;
  int instruction_register = 0;
  int operation_code = 0;
  int operand = 0;
  //
  int i = 0;
  while (getline(MyReadFile, myText)) {
    string command;
    int value;
    stringstream ss(myText);
    ss >> command >> value;

    cout << command << " " << value << endl;
    transform(command.begin(), command.end(), command.begin(), ::toupper);
    cout << command << " " << value << endl;
    memory[i] = COMBINE(opcodes[command], value);
    i++;
    // command
  }
  // Close the file
  MyReadFile.close();

  bool executing = true;
  while (executing) {
    instruction_register = memory[instruction_counter++];
    operation_code = instruction_register / 100;
    operand = instruction_register % 100;
    switch (operation_code) {
    case READ:
      cin >> memory[operand];
      // Read input and store it in memory
      break;
    case WRITE:
      cout << memory[operand];
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
      cout << "\nProgram is terminated!" << endl;
      executing = false;
      // Stop program
      break;
    default:
      cout << "\nUnknown operation " << executing << endl;
      // Unknown operation
      break;
    }
  }

  return 0;
}
