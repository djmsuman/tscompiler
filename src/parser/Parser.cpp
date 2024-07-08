#include "Parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Parser::Parser(Lexer &lexer)
    : lexer(lexer), currentToken(lexer.getNextToken()) {}

std::string Parser::parse() {
  std::string assembly;
  while (currentToken.type != TokenType::END_OF_FILE) {
    if (currentToken.type == TokenType::LET) {
      assembly += parseVariableDeclaration();
    } else if (currentToken.type == TokenType::CONST) {
      assembly += parseConstantDeclaration();
    } else if (currentToken.type == TokenType::IDENTIFIER) {
      assembly += parseAssignment();
    } else {
      throw std::runtime_error("Unexpected token: " + currentToken.value);
    }
  }
  return assembly;
}

void Parser::consume(TokenType type) {
  if (currentToken.type == type) {
    currentToken = lexer.getNextToken();
  } else {
    throw std::runtime_error("Unexpected token: " + currentToken.value);
  }
}

std::string Parser::parseVariableDeclaration() {
  consume(TokenType::LET);
  std::string variableName = currentToken.value;
  consume(TokenType::IDENTIFIER);
  consume(TokenType::EQUALS);
  std::string value = currentToken.value;
  consume(TokenType::NUMBER);
  consume(TokenType::SEMICOLON);

  std::stringstream assembly;
  assembly << "; Variable declaration: " << variableName << "\n";
  assembly << "push " << value << "\n";
  assembly << "pop " << variableName << "\n";
  return assembly.str();
}

std::string Parser::parseConstantDeclaration() {
  consume(TokenType::CONST);
  std::string constantName = currentToken.value;
  consume(TokenType::IDENTIFIER);
  consume(TokenType::EQUALS);
  std::string value = currentToken.value;
  consume(TokenType::NUMBER);
  consume(TokenType::SEMICOLON);

  std::stringstream assembly;
  assembly << "; Constant declaration: " << constantName << "\n";
  assembly << "push " << value << "\n";
  assembly << "pop " << constantName << "\n";
  return assembly.str();
}

std::string Parser::parseAssignment() {
  std::string variableName = currentToken.value;
  consume(TokenType::IDENTIFIER);
  consume(TokenType::EQUALS);
  std::string value = currentToken.value;
  consume(TokenType::NUMBER);
  consume(TokenType::SEMICOLON);

  std::stringstream assembly;
  assembly << "; Assignment: " << variableName << " = " << value << "\n";
  assembly << "push " << value << "\n";
  assembly << "pop " << variableName << "\n";
  return assembly.str();
}
