#include "parser/util.h"
#include <optional>
#include <string_view>

char State::cur() {
    if (input.empty()) {
        return '\0';
    } else if (pos.index >= input.size()) {
        return '\0';
    } else {
        return input[pos.index];
    }
}

char State::peek() {
    if (pos.index + 1 >= input.size()) {
        return '\0';
    }
    return input[pos.index + 1];
}

char State::consume() {
    if (pos.index >= input.size()) {
        return '\0';
    }
    char ret = input[pos.index];
    pos.index++;
    pos.column++;
    if (ret == '\n') {
        pos.line++;
        pos.column = 1;
    }
    return ret;
}

std::optional<std::string> State::peek(size_t n) {
    if (pos.index + n >= input.size()) {
        return std::nullopt;
    }
    std::string_view res = input.substr(pos.index, n);
    return std::make_optional(std::string(res));
}
