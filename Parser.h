#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include "Token.h"
#include "Lexer.h"

struct ASTNode;

enum class ASTNodeType {
  Program,
  Declaration,
  Assignment,
  Identifer,
  Literal,
  BinaryExp 
};

struct ASTNode {
  ASTNodeType type;
  std::string value;
  
  std::vector<std::unique_ptr<ASTNode>> children;

  ASTNode(ASTNodeType t, std::string val="")
    : type(t), value(std::move(val)) {}
};

using ProgramNode = ASTNode;

class Parser {
  public:
    Parser(const std::vector<Token>& tokens);

    std::unique_ptr<ProgramNode> parse();

  private:
    const std::vector<Token>& tokens_;
    size_t current_index = 0;

    const Token& peek() const;
    const Token& consume(TokenType expected_type, const std::string& context = "");

    // Grammars
    std::unique_ptr<ASTNode> parseProgram();

    std::unique_ptr<ASTNode> parseStatement(); 
    std::unique_ptr<ASTNode> parseDeclaration();
    std::unique_ptr<ASTNode> parseExp(); 
    // And more..
    ;
};

#endif PARSER_H
