#include <functional>
#include <iostream>
#include "parser/util.h"
#include "parser/combinator/basic.h"
#include "parser/rdd/basic.h"

int comibator_test() {
    State initial{"(a,b)", {0, 1, 1}};
    auto parser = pair(char_p('a'), char_p('b'));
    auto result = parser(initial);

    if (result.isSuccess()) {
      std::cout << "Parsed successfully: (" << result.get().first << ", "
                << result.get().second << ")\n";
      std::cout << "Remaining at line: " << result.getState().pos.line
                << ", column: " << result.getState().pos.column << "\n";
    } else {
      std::cerr << "Parse error: " << result.getError() << "\n";
    }
    return 0;
}

int rdd_test() {
    auto parser = RParser("a");
    auto result = parser.char_p('a');
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
    }
    return 0;
}


int main() {
    rdd_test();
}
