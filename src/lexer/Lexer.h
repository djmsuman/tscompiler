#pragma once
#include <string>
#include "../common/Token.h"

class Lexer {
 public:
  Lexer(const std::string &source);
  Token getNextToken();

 private:
  std::string source;
  size_t position;

  void skipWhitespace();
  Token lexIdentifier();
  Token lexNumber();
  Token lexOperator();
  Token lexDelimiter();
};
