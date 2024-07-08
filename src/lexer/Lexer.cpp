#include "Lexer.h"
#include <stdexcept>
#include "../common/TokenList.h"
#include "../utils/string.h"

Lexer::Lexer(const std::string &source) : source(source), position(0) {}

Token Lexer::getNextToken() {
  skipWhitespace();

  if (position >= source.length()) {
    return {TokenType::END_OF_FILE, ""};
  }

  if (isalpha(source[position])) {
    return lexIdentifier();
  }

  if (isdigit(source[position])) {
    return lexNumber();
  }

  if (isoperator(source[position])) {
    return lexOperator();
  }

  if (isdelimiter(source[position])) {
    return lexDelimiter();
  }

  throw std::runtime_error(
      "Unexpected character: " + std::string(1, source[position]));
}

void Lexer::skipWhitespace() {
  while (position < source.length() && isspace(source[position])) {
    position++;
  }
}

Token Lexer::lexIdentifier() {
  size_t start = position;
  while (position < source.length() &&
         (isalnum(source[position]) || isunderscore(source[position]))) {
    position++;
  }

  std::string value = source.substr(start, position - start);

  if (value == _TOKEN_LET) {
    return {TokenType::LET, value};
  } else if (value == _TOKEN_CONST) {
    return {TokenType::CONST, value};
  }
  return {TokenType::IDENTIFIER, value};
}

Token Lexer::lexNumber() {
  size_t start = position;
  while (position < source.length() && isdigit(source[position])) {
    position++;
  }

  std::string value = source.substr(start, position - start);

  return {TokenType::NUMBER, value};
}

Token Lexer::lexOperator() {
  position++;

  std::string value = std::string(1, _TOKEN_EQUAL);

  return {TokenType::EQUALS, value};
}

Token Lexer::lexDelimiter() {
  position++;

  std::string value = std::string(1, _TOKEN_SEMICOLON);

  return {TokenType::SEMICOLON, value};
}
