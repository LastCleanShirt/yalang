#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Lexer.h"
#include "Token.h"

std::string readFileIntoString(const std::string& filePath) {
  std::ifstream inputFile(filePath);

  if (!inputFile.is_open()) {
    std::cerr  << "Error: File could not be opened" << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << inputFile.rdbuf();

  inputFile.close();

  return buffer.str();
}

int main(int argc, char* argv[]) {
  std::string current_exec_name = argv[0]; // Name of the current exec program
  std::vector<std::string> all_args;

  if (argc > 1) {
    all_args.assign(argv + 1, argv + argc);
  }

  Lexer lex(readFileIntoString(all_args[0]));
  std::vector<Token> a = lex.tokenize();

  for (const auto& token : a) {
    std::cout << "(Type: " << static_cast<int>(token.type)
              << ", value: [" << token.val << "])\n";
  }

  return 0;
}

