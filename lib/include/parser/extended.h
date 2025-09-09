#pragma once

#include "parser/basic.h"
#include "parser/util.h"
#include <utility>

class ExtendedParser : public Parser {
 public:
  ExtendedParser(const State& state) : Parser(state) {}
  ExtendedParser(const std::string& input) : Parser(input) {}
  ExtendedParser(const ExtendedParser& other) : Parser(other) {}
  ~ExtendedParser() {}
  PResult<std::pair<char, char>> char_p2(char c1, char c2);
};
