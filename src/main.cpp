#include <fstream>
#include <iostream>
#include <sstream>
#include "compiler/Compiler.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <source.ts> -o <output.asm>"
              << std::endl;
    return 1;
  }

  std::string inputFile = argv[1];
  std::string outputFlag = argv[2];
  std::string outputFile = argv[3];

  if (outputFlag != "-o") {
    std::cerr << "Invalid output flag. Use -o." << std::endl;
    return 1;
  }

  // Read input file
  std::ifstream inFile(inputFile);
  if (!inFile) {
    std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
    return 1;
  }

  std::stringstream buffer;
  buffer << inFile.rdbuf();
  std::string sourceCode = buffer.str();

  try {
    // Compile the source code
    std::string assemblyCode = Compiler::compile(sourceCode);

    // Write to output file
    std::ofstream outFile(outputFile);
    if (!outFile) {
      std::cerr << "Error: Unable to open output file " << outputFile
                << std::endl;
      return 1;
    }

    outFile << assemblyCode;
    std::cout << "Compilation successful. Output written to " << outputFile
              << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Compilation error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
