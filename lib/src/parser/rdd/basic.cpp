#include "parser/rdd/basic.h"
#include "parser/util.h"
#include <cstddef>
#include <string>

PResult<char> RParser::anyChar() {
  if (state.input.empty()) {
    return PResult<char>::error(state, "anyChar: end of input");
  }
  if (state.getCurrentChar() == '\0') {
    return PResult<char>::error(state, "anyChar: end of input");
  }
  return PResult<char>::success(state.consume(), state);
}

PResult<char> RParser::char_p(char c) {
  if (state.getCurrentChar() == c) {
    return PResult<char>::success(state.consume(), state);
  }
  return PResult<char>::error(state,
                              "char_p: expected '" + std::string(1, c) + "'");
}

PResult<std::string> RParser::parseWhile(std::function<bool(char)> predicate) {
  std::string result;
  while (predicate(state.getCurrentChar())) {
    result += state.consume();
  }
  return PResult<std::string>::success(result, state);
}

PResult<std::nullptr_t> RParser::ws() {
  while (state.getCurrentChar() == ' ' || state.getCurrentChar() == '\t') {
    state.consume();
  }
  return PResult<std::nullptr_t>::success(NULL, state);
}

PResult<std::nullptr_t> RParser::wsn() {
  while (state.getCurrentChar() == ' ' || state.getCurrentChar() == '\t' ||
         state.getCurrentChar() == '\n') {
    state.consume();
  }
  return PResult<std::nullptr_t>::success(NULL, state);
}
