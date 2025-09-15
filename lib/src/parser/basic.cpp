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
    this->consume(s.size());
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

PResult<int> Parser::int_p() {
  std::string result;
  bool success = false;
  while (this->cur() >= '0' && this->cur() <= '9') {
    success = true;
    result += this->consume();
  }
  if (success) {
    return PResult<int>::success(std::stoi(result), this->getPos());
  } else {
    return PResult<int>::error(this->getPos(), "int_p: expected integer");
  }
}

PResult<double> Parser::double_p() {
  std::string result;
  bool decimal_point = false;
  bool success = false;
  while ((this->cur() >= '0' && this->cur() <= '9') || this->cur() == '.') {
    success = true;
    if (this->cur() == '.') {
      result += this->consume();
      decimal_point = true;
      break;
    } else {
      result += this->consume();
    }
  }
  if (decimal_point && success) {
    while (this->cur() >= '0' && this->cur() <= '9') {
      result += this->consume();
    }
  }
  if (success) {
    return PResult<double>::success(std::stod(result), this->getPos());
  } else {
    return PResult<double>::error(this->getPos(), "double_p: expected float");
  }
}

PResult<std::string> Parser::ident_p() {
  std::string result;
  // first charachter should be a letter or underscore
  if ((cur() >= 'a' && cur() <= 'z') || (cur() >= 'A' && cur() <= 'Z') ||
      cur() == '_') {
    result += this->consume();
  } else {
    return PResult<std::string>::error(
        this->getPos(), "identifier: expected letter or underscore");
  }
  // the rest can be letters, numbers, or underscores
  while ((cur() >= 'a' && cur() <= 'z') || (cur() >= 'A' && cur() <= 'Z') ||
         (cur() >= '0' && cur() <= '9') || cur() == '_') {
    result += this->consume();
  }
  return PResult<std::string>::success(result, this->getPos());
}
