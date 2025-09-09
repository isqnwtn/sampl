#include "parser/util.h"
#include <utility>
#include "parser/extended.h"

PResult<std::pair<char,char>> ExtendedParser::char_p2(char c1, char c2) {
    if (cur()!= '('){
        return PResult<std::pair<char,char>>::error(getPos(),"char_p2: expected '('");
    }
    consume();

    this->ws();

    if (cur() != c1) {
        return PResult<std::pair<char,char>>::error(getPos(),"char_p2: expected '" + std::string(1, c1) + "'");
    }
    consume();

    this->ws();

    if (cur() != ',') {
        return PResult<std::pair<char,char>>::error(getPos(),"char_p2: expected ','");
    }
    consume();

    ws();

    if (cur() != c2) {
        return PResult<std::pair<char,char>>::error(getPos(),"char_p2: expected '" + std::string(1, c2) + "'");
    }
    consume();

    this->ws();

    if (cur() != ')') {
        return PResult<std::pair<char,char>>::error(getPos(),"char_p2: expected ')'");
    }
    consume();

    return PResult<std::pair<char,char>>::success(std::make_pair(c1,c2), getPos());
}
