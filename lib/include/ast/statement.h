#pragma once
#include "ast/expr.h"
#include <string>

namespace stmt {

enum StmtType { AssignmentT, ReturnT };

class Stmt {
public:
  virtual ~Stmt() = default;
  virtual StmtType getType() = 0;
  virtual std::string toString() = 0;
};

using StmtPtr = std::unique_ptr<Stmt>;

class Assignment : public Stmt {
public:
  Assignment(std::string name, expr::ExprPtr expr)
      : name(name), expr(std::move(expr)) {}
  StmtType getType() { return StmtType::AssignmentT; }
  std::string toString() {
    return "Assignment(" + name + ", " + expr->toString() + ")";
  }

private:
  std::string name;
  expr::ExprPtr expr;
};

class Return : public Stmt {
public:
  Return(expr::ExprPtr expr) : expr(std::move(expr)) {}
  StmtType getType() { return StmtType::ReturnT; }
  std::string toString() { return "Return(" + expr->toString() + ")"; }

private:
  expr::ExprPtr expr;
};
} // namespace stmt
