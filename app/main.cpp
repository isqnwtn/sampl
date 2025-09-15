#include <iostream>
#include "parser/expr.h"
#include "parser/statement.h"
#include "parser/util.h"
#include "parser/basic.h"
#include "parser/extended.h"

int test() {

    // simple parser
    std::string s0 = "a";
    auto parser = Parser(s0);
    auto result = parser.char_p('a');
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
    }

    // more complicated exmaple
    std::string s = "(   a ,b )(c,d)";
    auto state = State(s);

    auto parser2 = ExtendedParser(state);
    auto result2 = parser2.char_p2('a','b');
    if ( result2.isSuccess()) {
        std::cout << "Parsed successfully: (" << result2.get().first << ", " << result2.get().second << ")\n";
    } else {
        std::cerr << "Parse error: " << result2.getError() << "\n";
    }
    auto p3 = ExtendedParser(parser2);
    auto r3 = p3.char_p2('c','d');
    if ( r3.isSuccess()) {
        std::cout << "Parsed successfully: (" << r3.get().first << ", " << r3.get().second << ")\n";
    } else {
        std::cerr << "Parse error: " << r3.getError() << "\n";
    }

    // parsing floating point numbers
    std::string s2 = "21.23";
    Parser parser3(s2);
    auto result3 = parser3.double_p();
    if ( result3.isSuccess()) {
        std::cout << "Parsed successfully: " << result3.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result3.getError() << "\n";
    }

    return 0;
}

int test2() {
    std::string s = "abh_jji21_";
    Parser parser(s);
    auto result = parser.ident_p();
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get() << "\n";
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
    }
    return 0;
}

int test3() {
    std::string s = "ident * ( a + 12 )";
    ExprParser parser(s);
    auto result = parser.expr();
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get()->toString() << "\n";
        return 0;
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
        return -1;
    }
}

int test4() {
    std::string s = "return a*c";
    StmtParser parser(s);
    auto result = parser.parseStatement();
    if ( result.isSuccess()) {
        std::cout << "Parsed successfully: " << result.get()->toString() << "\n";
        return 0;
    } else {
        std::cerr << "Parse error: " << result.getError() << "\n";
        return -1;
    }
}


int main() {
    // test();
    // test2();
    // test3();
    test4();
}
