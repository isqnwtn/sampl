#pragma once

#include <memory>
#include <string>

namespace expr {

enum ExprType { INT, FLOAT, BOOL, STRING, IDENTIFIER, BINOP, GROUP };

class Expression {
public:
  virtual ~Expression() = default;
  virtual ExprType getType() const = 0;
  virtual std::string toString() const = 0;
};

using ExprPtr = std::unique_ptr<Expression>;

class IntValue final : public Expression {
  int value;

public:
  IntValue(int value) : value(value) {}
  virtual ~IntValue() = default;
  int getValue() const { return value; }
  ExprType getType() const override { return INT; }
  std::string toString() const override { return std::to_string(value); }
};

class FloatValue final : public Expression {
  double value;

public:
  virtual ~FloatValue() = default;
  double getValue() const { return value; }
  ExprType getType() const override { return FLOAT; }
  std::string toString() const override { return std::to_string(value); }
};

class BoolValue final : public Expression {
  bool value;

public:
  virtual ~BoolValue() = default;
  bool getValue() const { return value; }
  ExprType getType() const override { return BOOL; }
  std::string toString() const override { return value ? "true" : "false"; }
};

class StringValue final : public Expression {
  std::string value;

public:
  virtual ~StringValue() = default;
  std::string getValue() const { return value; }
  ExprType getType() const override { return STRING; }
  std::string toString() const override { return value; }
};

class Identifier final : public Expression {
  std::string ident;

public:
  Identifier(std::string ident) : ident(std::move(ident)) {}
  virtual ~Identifier() = default;
  std::string getIdent() const { return ident; }
  ExprType getType() const override { return IDENTIFIER; }
  std::string toString() const override { return ident; }
};

enum Op { PLUS, MINUS, MULT, DIV };
std::string opToString(Op op);

class BinOp final : public Expression {
  ExprPtr left;
  ExprPtr right;
  Op op;

public:
  BinOp(ExprPtr left, ExprPtr right, Op op)
      : left(std::move(left)), right(std::move(right)), op(op) {}
  virtual ~BinOp() = default;
  ExprPtr &getLeft() { return left; }
  ExprPtr &getRight() { return right; }
  ExprType getType() const override { return BINOP; }
  std::string toString() const override {
    return left->toString() + " " + opToString(op) + " " + right->toString();
  }
};

class GroupExpr final : public Expression {
  ExprPtr expr;

public:
  GroupExpr(ExprPtr expr) : expr(std::move(expr)) {}
  virtual ~GroupExpr() = default;
  ExprPtr &getExpr() { return expr; }
  ExprType getType() const override { return GROUP; }
  std::string toString() const override { return "(" + expr->toString() + ")"; }
};

} // namespace exp
