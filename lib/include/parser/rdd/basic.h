#include "parser/util.h"
#include <cstddef>
#include <string>
#include <functional>

class RParser {
 State state;
 public:
  RParser(State state) : state(state) {}
  RParser(const std::string input) : state(State{input, Position{0,1,1}}) {}
  ~RParser() {}
  State getState() const { return state; }
  void setState(State state) { this->state = state; }
  // primary parsers
  PResult<char> anyChar();
  PResult<char> char_p(char c);
  PResult<std::string> parseWhile(std::function<bool(char)> predicate);
  PResult<std::nullptr_t> ws();
  PResult<std::nullptr_t> wsn();
};
