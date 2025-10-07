#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
  Identifier,
  Keyword,
  String,
  Char,
  Literal,
  Operator,
  Separator,
  End
};

struct Token {
  TokenType type;
  std::string val; 
};


inline std::string tokenTypeToString(TokenType type) {
  switch (type) {
    case TokenType::Identifier: return "Identifier";
    case TokenType::Keyword:    return "Keyword";
    case TokenType::String:     return "String";
    case TokenType::Char:       return "Char";
    case TokenType::Literal:    return "Literal";
    case TokenType::Operator:   return "Operator";
    case TokenType::Separator:  return "Separator";
    case TokenType::End:        return "End";
    default:                    return "Unknown";
  }
}

#endif
