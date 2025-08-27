#include <iostream>
#include "parser/util.h"
#include "parser/basic.h"
#include "parser/extended.h"

int test() {
    auto parser = Parser("a");
    auto result = parser.char_p('a');
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
    }
    auto parser2 = EParser("(  a ,   b)");
    auto result2 = parser2.char_p2('a','b');
    if ( result2.isSuccess()) {
        std::cout << "Parsed successfully: (" << result2.get().first << ", " << result2.get().second << ")\n";
    } else {
        std::cerr << "Parse error: " << result2.getError() << "\n";
    }

    return 0;
}


int main() {
    test();
}
