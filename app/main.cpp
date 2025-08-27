#include <iostream>
#include "parser/util.h"
#include "parser/basic.h"
#include "parser/extended.h"

int test() {

    // simple parser
    auto parser = Parser("a");
    auto result = parser.char_p('a');
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
    }

    // more complicated exmaple
    auto state = State("(  a ,   b)(c,d)");
    auto parser2 = EParser(state);
    auto result2 = parser2.char_p2('a','b');
    if ( result2.isSuccess()) {
        std::cout << "Parsed successfully: (" << result2.get().first << ", " << result2.get().second << ")\n";
    } else {
        std::cerr << "Parse error: " << result2.getError() << "\n";
    }
    auto p3 = EParser(parser2);
    auto r3 = p3.char_p2('c','d');
    if ( r3.isSuccess()) {
        std::cout << "Parsed successfully: (" << r3.get().first << ", " << r3.get().second << ")\n";
    } else {
        std::cerr << "Parse error: " << r3.getError() << "\n";
    }

    return 0;
}


int main() {
    test();
}
