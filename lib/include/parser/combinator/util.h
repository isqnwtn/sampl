#pragma once
#include <string>
#include <optional>
#include <string_view>

struct Position {
    size_t index;
    size_t line;
    size_t column;
};

struct State {
    std::string_view input;
    Position pos;
};

template<typename T>
class PResult {
public:
    // Constructing a successful result
    PResult(T value, State state): value(std::make_optional(value)), state(state), error("") {}
    // Constructing an error while parsing
    PResult(State state, std::string error): value(std::nullopt), state(state), error(error) {}

    // Static function to easily understand that it's an error
    static PResult Error(State state, std::string error){
        return PResult(state, error);
    }
    ~PResult() {}
    std::optional<T> value;
    State state;
    std::string error;
};
