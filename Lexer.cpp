#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
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
      if (c == '/') {
        if (peek_next() == '/') {
          while (!isAtEnd() && peek() != '\n') advance();
        } else {
          tokens.push_back(Token{TokenType::Operator, std::string(1, c)});
          advance();
        }
      } else {
        tokens.push_back(Token{TokenType::Operator, std::string(1, c)});
        advance();
      }
    }
    // String
    else if (c == '"') {
      advance(); // Ignore the "
      std::string temp;

      while (!isAtEnd() && peek() != '"' && peek() != '\n') {
        temp += advance();
      }
      if (peek() == '\n') {
        Error err{ErrorType::SyntaxError, " \" Expected", start_line, start_column};
        err.print();
      }
      else if (!isAtEnd()) {
        advance();
        tokens.push_back(Token{TokenType::String, temp});
      }
    }
    


// TODO: NOTE, variabel yang diawali dari angka, kasih error, untuk skrg fokus ke identifier aja dulu
    // Identifier
    else if (isIdentifier(c)) {
      //std::cout << "Found identifier" << std::endl;
      std::string temp;
      while(!isAtEnd() && isIdentifier(peek()) && peek() != '\n') {
        temp += advance();
      }

      if (!isAtEnd()) {
        advance();
        if (Lexer::isKeyword(temp)) tokens.push_back(Token{TokenType::Keyword, temp});
        else tokens.push_back(Token{TokenType::Identifier, temp});
      }

      
    }
    else {
      advance();
    }


  }

  return tokens;

};


bool Lexer::isAtEnd() const {
  return pos >= source.size();
}

char Lexer::peek() const {
  if (pos >= source.size()) return '\0';
  if (isAtEnd()) return '\0';
  return source[pos];
}

char Lexer::peek_next() const {
  if (pos >= source.size()) return '\0';
  if (isAtEnd()) return '\0';
  return source[pos+1];
}

char Lexer::advance() {
  if (pos >= source.size()) {
      std::cerr << "\n[BUG] Reading past end of file at index "
                << pos << " (size = " << source.size() << ")\n";
      abort();
  } else {
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
     
}

bool Lexer::isOperator(char c) const {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '=';
}

bool Lexer::isIdentifier(char c) const{
  return std::string("abcdefghijklmnopqrstuvwxyz_").find(c) != std::string::npos;
}

bool Lexer::isKeyword(std::string c) const {
  static const std::unordered_set<std::string> keywords = {
    "start", "end",
    "if", "else",
    "for", "while", "do",
    "return",
    "int", "flt", "bool", "str",
    "true", "false"
  };
  
  return keywords.find(c) != keywords.end();
}
