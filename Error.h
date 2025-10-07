#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

enum class ErrorType {
  SyntaxError,
  RuntimeError,
  TypeError
};


struct Error {
  ErrorType type;
  std::string msg;
  int line;
  int column;

  void print() const {
    std::cerr << "[Error]"
              << "(" << line << ":" << column << ")"
              << msg << std::endl;
  };
};

#endif
