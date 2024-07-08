#pragma once
#include <string>
#include "../lexer/Lexer.h"

class Parser {
 public:
  Parser(Lexer &lexer);
  std::string parse();

 private:
  Lexer &lexer;
  Token currentToken;

  void consume(TokenType type);
  std::string parseVariableDeclaration();
  std::string parseConstantDeclaration();
  std::string parseAssignment();
};
