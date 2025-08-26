#include <functional>
#include <iostream>
#include "parser/combinator/util.h"
#include "parser/combinator/basic.h"

int main() {
  State initial{"(a,b)", {0, 1, 1}};
  auto parser = pair(char_p('a'), char_p('b'));
  auto result = parser(initial);

  if (result.value) {
    std::cout << "Parsed successfully: (" << result.value->first << ", "
              << result.value->second << ")\n";
    std::cout << "Remaining at line: " << result.state.pos.line
              << ", column: " << result.state.pos.column << "\n";
  } else {
    std::cerr << "Parse error: " << result.error << "\n";
  }
}
