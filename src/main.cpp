#include "VirtualMachine.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {

  std::cout << argc << std::endl;

  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  if (argc <= 1 || argc > 2) {
    std::cout << "No arguments provided" << std::endl;
    return 0;
  }
  std::string rawFile = argv[1];
  std::ifstream MyReadFile(rawFile);
  //

  VirtualMachine vm;
  vm.readFile(MyReadFile).loadProgram();
  vm.run();
  return 0;
}
