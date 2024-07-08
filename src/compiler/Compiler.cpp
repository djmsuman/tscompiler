#include "Compiler.h"
#include "../lexer/Lexer.h"
#include "../parser/Parser.h"

std::string Compiler::compile(const std::string &sourceCode) {
  Lexer lexer(sourceCode);
  Parser parser(lexer);
  return parser.parse();
}
