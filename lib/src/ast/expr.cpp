#include "ast/expr.h"

namespace expr {
std::string opToString(Op op) {
  switch (op) {
  case PLUS:
    return "+";
  case MINUS:
    return "-";
  case MULT:
    return "*";
  case DIV:
    return "/";
  default:
    return "?";
  }
}

} // namespace expr
