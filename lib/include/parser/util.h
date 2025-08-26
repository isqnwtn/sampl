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
    char getCurrentChar() {
        if (input.empty()) {
            return '\0';
        }
        return input[pos.index];
    }
    char peek() {
        if (pos.index + 1 >= input.size()) {
            return '\0';
        }
        return input[pos.index + 1];
    }
    char consume() {
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
};

template<typename T>
class PResult {
public:
    // Constructing a successful result
    PResult(T value, State state): value(std::make_optional(value)), state(state), error_msg("") {}
    // Constructing an error while parsing
    PResult(State state, std::string error): value(std::nullopt), state(state), error_msg(error) {}

    // Static function to easily understand that it's an error
    static PResult error(State state, std::string error){
        return PResult(state, error);
    }
    // Static function to easily understand that it's a success
    static PResult<T> success(T value,State state){
        return PResult(value, state);
    }

    inline bool isSuccess() const {
        return value.has_value();
    }
    inline bool isError() const {
        return !isSuccess();
    }

    inline const T& get() const {
        return value.value();
    }

    inline const State& getState() const {
        return state;
    }

    inline std::string getError() const {
        return error_msg;
    }

    // destructor
    ~PResult() {}

    // members
    std::optional<T> value;
    State state;
    std::string error_msg;
};
