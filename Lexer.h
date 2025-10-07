#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
  public:
    Lexer(const std::string& input);

    std::vector<Token> tokenize();
  private:
    std::string source;
    size_t pos = 0;
    int line, column;

    char peek() const;
    char advance();
    bool isAtEnd() const;
    bool isOperator(char c) const;
    bool isIdentifier(char c) const;
};


#endif
