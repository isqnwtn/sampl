#include "parser/basic.h"
#include "parser/util.h"
#include <cstddef>
#include <string>

PResult<char> Parser::anyChar() {
  if (this->isInputEmpty()) {
    return PResult<char>::error(this->getPos(), "anyChar: empty input");
  }
  if (this->cur() == '\0') {
    return PResult<char>::error(this->getPos(), "anyChar: end of input");
  }
  return PResult<char>::success(this->consume(), this->getPos());
}

PResult<char> Parser::char_p(char c) {
  if (this->cur() == c) {
    return PResult<char>::success(this->consume(), this->getPos());
  }
  return PResult<char>::error(this->getPos(),
                              "char_p: expected '" + std::string(1, c) + "'");
}

PResult<std::string> Parser::pstr(std::string s) {
  if (this->peek(s.size()) == s) {
    return PResult<std::string>::success(s, this->getPos());
  }
  return PResult<std::string>::error(this->getPos(),
                                     "pstr: expected '" + s + "'");
}

PResult<std::string> Parser::parseWhile(std::function<bool(char)> predicate) {
  std::string result;
  while (predicate(this->cur())) {
    result += this->consume();
  }
  return PResult<std::string>::success(result, this->getPos());
}

PResult<std::nullptr_t> Parser::ws() {
  while (this->cur() == ' ' || this->cur() == '\t') {
    this->consume();
  }
  return PResult<std::nullptr_t>::success(NULL, this->getPos());
}

PResult<std::nullptr_t> Parser::wsn() {
  while (this->cur() == ' ' || this->cur() == '\t' || this->cur() == '\n') {
    this->consume();
  }
  return PResult<std::nullptr_t>::success(NULL, this->getPos());
}
