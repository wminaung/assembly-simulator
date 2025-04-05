#include "instructions.h"
#include <iostream>

#define COMBINE(op, addr) ((op)*100 + (addr))
using namespace std;
int main() {
  int memory[100] = {0};
  int accumulator = 0;
  int instruction_counter = 0;
  int instruction_register = 0;
  int operation_code = 0;
  int operand = 0;

  // LOAD PROGRAM INTO MEMORY
  /*
    memory[0] = 1050; // read input from memory 50
    memory[1] = 2050; // load to accumulator
    memory[2] = 1051; // read input from memory 51
    memory[3] = 3051; // add value from m 51 to accumulator
    memory[4] = 2152; // store accumulator value in memory
    memory[5] = 1152; // write accumulator value to memory
    memory[6] = 4300; // halt
  */
  memory[0] = COMBINE(READ, 50);  // read input from memory 50
  memory[1] = COMBINE(LOAD, 50);  // load to accumulator
  memory[2] = COMBINE(READ, 51);  // read input from memory 51
  memory[3] = COMBINE(SUB, 51);   // add value from m 51 to accumulator
  memory[4] = COMBINE(STORE, 52); // store accumulator value in memory
  memory[5] = COMBINE(WRITE, 52); // write accumulator value to memory
  memory[6] = COMBINE(HALT, 00);  // halt

  // EXECUTE PROGRAM
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
    case JUPZERO:
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

  ////////////////////////
  return 0;
  //
}
