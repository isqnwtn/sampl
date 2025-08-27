#pragma once

#include "parser/util.h"
#include <cstddef>
#include <string>
#include <functional>

class Parser : public State {
 public:
 // Constructor
  Parser(State state) : State(state) {}
  Parser(const std::string& input) : State(input) {}
  ~Parser() {}

  // Helpers
  Position getPos() const { return this->stateGetPos(); }
  void setPos(Position pos) { this->stateSetPos(pos); }
  // consumer helpers
  char cur() { return this->stateGetCurrentChar(); }
  char peek() { return this->statePeek(); }
  char consume() { return this->stateConsume(); }

  // utility helpers
  bool isInputEmpty() { return this->input.empty(); }
  bool isNullChar() { return this->cur() == '\0'; }

  // primary parsers
  PResult<char> anyChar();
  PResult<char> char_p(char c);
  PResult<std::string> parseWhile(std::function<bool(char)> predicate);
  PResult<std::nullptr_t> ws();
  PResult<std::nullptr_t> wsn();
};
