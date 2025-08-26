#include "parser/util.h"
#include "parser/combinator/basic.h"
#include <functional>
#include <string>


State advance(const State& st, char c) {
    State next = st;
    next.pos.index++;
    if (c == '\n') {
        next.pos.line++;
        next.pos.column = 1;
    } else {
        next.pos.column++;
    }
    return next;
}

Parser<char> satisfy(std::function<bool(char)> pred, std::string expected) {
  return [pred, expected](State st) -> PResult<char> {
    if (st.pos.index >= st.input.size()) {
      return PResult<char>::error(st, "Unexpected end of input, expected: " +
                                          expected);
    }
    char c = st.input[st.pos.index];
    if (pred(c)) {
      State next = advance(st, c);
      return PResult<char>(c, next);
    } else {
      return PResult<char>::error(
          st, "Unexpected '" + std::string(1, c) + "' at line " +
                  std::to_string(st.pos.line) + ", column " +
                  std::to_string(st.pos.column) + ", expected: " + expected);
    }
  };
}

Parser<char> char_p(char expected) {
  return satisfy([expected](char c) { return c == expected; },
                 std::string(1, expected));
}
