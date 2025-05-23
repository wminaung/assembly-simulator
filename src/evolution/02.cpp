#include "instructions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define COMBINE(op, addr) ((op)*100 + (addr))
using namespace std;

string getSpace(int const &stri_len) {
  std::string space;
  if (stri_len == 2) {
    space = "  |  ";
  } else if (stri_len == 1) {
    space = "  |   ";
  }
  return space;
}

void printMemory(int const (&memory)[100], int program_counter = 0,
                 int accumulator = 0) {
  // Print header
  cout << "Memory Program Counter " << program_counter << endl;
  cout << "---------------" << endl;

  // Loop to print memory from 0 to 8 and 50 to 58 side by side
  for (size_t i = 0; i < 9; i++) { // From index 0 to 8
    std::ostringstream oss;
    oss << i;
    string stri = oss.str();
    string space = getSpace(stri.length());

    // Prepare the first column for indices 0 to 8
    cout << "| " << stri << space << memory[i] << "    |";

    // Prepare the second column for indices 50 to 58
    if (i + 50 < 100) { // Ensure we don't access out-of-bounds memory
      std::ostringstream oss2;
      oss2 << (i + 50);
      string stri2 = oss2.str();
      string space2 = getSpace(stri2.length());
      cout << "| " << stri2 << space2 << memory[i + 50] << "    |" << endl;
    } else {
      cout << "|        |" << endl; // To keep the format aligned if there are
                                    // less than 9 items in the second range
    }
    cout << "---------------" << endl;
  }
  cout << "Accumulator: " << accumulator << endl;
}

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

    // cout << command << " " << value << endl;
    transform(command.begin(), command.end(), command.begin(), ::toupper);
    // cout << command << " " << value << endl;
    memory[i] = COMBINE(opcodes[command], value);
    i++;
    // command
  }
  // Close the file
  MyReadFile.close();

  printMemory(memory);
  bool executing = true;
  while (executing) {

    instruction_register = memory[instruction_counter];
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
    instruction_counter++;
    printMemory(memory, instruction_counter, accumulator);
  }

  return 0;
}
