#pragma once
#include <string>

enum class TokenType {
  LET,
  CONST,
  IDENTIFIER,
  NUMBER,
  EQUALS,
  SEMICOLON,
  UNDERSCORE,
  END_OF_FILE
};

struct Token {
  TokenType type;
  std::string value;
};
