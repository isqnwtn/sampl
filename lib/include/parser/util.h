#pragma once
#include <optional>
#include <string>
#include <string_view>

struct Position {
  size_t index;
  size_t line;
  size_t column;
};

struct State {
  std::string_view input;
  Position pos;

  // Constructor
  State(const State &state) : input(state.input), pos(state.pos) {}
  State(const std::string &input) : input(input), pos(Position{0, 1, 1}) {}

  // Members
  Position getPos() const { return this->pos; }
  void setPos(Position pos) { this->pos = pos; }

  char cur();
  char peek();
  std::optional<std::string> peek(size_t n);
  char consume();
  int consume(int len);
};

template <typename T> class PResult {
public:
  // Constructing a successful result
  PResult(T &&value, Position state)
      : value(std::move(value)), pos(state), error_msg("") {
  }
  // Constructing an error while parsing
  PResult(Position state, std::string error)
      : value(std::nullopt), pos(state), error_msg(error) {}

  // explicit definitions for disabling copy and allowing move
  PResult(const PResult &) = delete;            // disable copy
  PResult &operator=(const PResult &) = delete; // disable copy assignment

  PResult(PResult &&) = default;            // allow move
  PResult &operator=(PResult &&) = default; // allow move assignment

  ~PResult() = default; // destructor (defaulted!)
  // ~PResult() {}

  // members
  std::optional<T> value;
  Position pos;
  std::string error_msg;

  // Helpers

  // Static function to easily understand that it's an error
  static PResult error(Position pos, std::string error) {
    return PResult(pos, error);
  }
  // Static function to easily understand that it's a success
  static PResult<T> success(T value, Position pos) {
    return PResult(std::move(value), pos);
  }

  inline bool isSuccess() const { return value.has_value(); }
  inline bool isError() const { return !isSuccess(); }

  inline const T &get() const { return value.value(); }

  inline T yield() { return std::move(value.value()); }

  inline const Position &getState() const { return pos; }

  inline std::string getError() const { return error_msg; }
};
