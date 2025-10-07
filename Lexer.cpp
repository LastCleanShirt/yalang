#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"
#include "Error.h"

Lexer::Lexer(const std::string& input)
  : source(input), pos(0), line(1), column(1) {};

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;

  while (!isAtEnd()) {
    int start_line = line;
    int start_column = column;
    char c = peek();
    
    if (isdigit(c)){
      std::string temp;

      while(isdigit(peek())) {
        temp+=advance();
      }

      tokens.push_back(Token{TokenType::Literal, temp});

    }

    else if (isOperator(c)) {
      tokens.push_back(Token{TokenType::Operator, std::string(1, c)});
      advance();
    }
    // String
    else if (c == '"') {
      advance();
      std::string temp;

      while (!isAtEnd() && peek() != '"') {
        temp += advance();
      }

      if (peek() == '"'){
        advance();
      } /*else{
        Error err{ErrorType::SyntaxError, "'\"' expected", line, column}; 
        err.print();
      }*/

      tokens.push_back(Token{TokenType::String, temp});
    }

    else {
      advance();
    }


  }

  return tokens;

};


bool Lexer::isAtEnd() const {
  return pos >= source.length();
}

char Lexer::peek() const {
  if (isAtEnd()) return '\0';
  return source[pos];
}

char Lexer::advance() {
  if (isAtEnd()) return '\0';
  char c = source[pos];
  pos++;
  if (c=='\n'){
    line++;
    column = 1;
  } else {
    column++;
  }

  return c;
   
}

bool Lexer::isOperator(char c) const {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '=';
}
