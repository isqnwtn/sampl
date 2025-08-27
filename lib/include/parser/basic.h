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
  Parser(const Parser& parser): State(parser) {}
  ~Parser() {}

  // utility helpers
  bool isInputEmpty() { return this->input.empty(); }
  bool isNullChar() { return this->cur() == '\0'; }

  // primary parsers
  PResult<char> anyChar();
  PResult<char> char_p(char c);
  PResult<std::string> pstr(std::string s);
  PResult<std::string> parseWhile(std::function<bool(char)> predicate);
  PResult<std::nullptr_t> ws();
  PResult<std::nullptr_t> wsn();
};
