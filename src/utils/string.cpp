#include "string.h"
#include "../common/TokenList.h"

bool isunderscore(int ch) {
  return ch == _TOKEN_UNDERSCORE;
}

bool isoperator(int ch) {
  return ch == _TOKEN_EQUAL;
}

bool isdelimiter(int ch) {
  return ch == _TOKEN_SEMICOLON;
}
