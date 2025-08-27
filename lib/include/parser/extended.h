#pragma once

#include "parser/basic.h"
#include "parser/util.h"
#include <utility>

class EParser : public Parser {
 public:
  EParser(const State& state) : Parser(state) {}
  EParser(const std::string& input) : Parser(input) {}
  ~EParser() {}
  PResult<std::pair<char, char>> char_p2(char c1, char c2);
};
