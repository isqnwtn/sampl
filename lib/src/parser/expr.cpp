#include "parser/expr.h"
#include "ast/expr.h"
#include "parser/util.h"
#include <string>

PResult<expr::ExprPtr> ExprParser::integer() {
  this->ws();
  auto val = this->int_p();
  if (val.isSuccess()) {
    this->ws();
    expr::ExprPtr res = std::make_unique<expr::IntValue>(val.get());
    return PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
  } else {
    return PResult<expr::ExprPtr>::error(this->getPos(), "expected integer");
  }
}

PResult<expr::ExprPtr> ExprParser::identifier() {
  this->ws();
  auto parsed = this->ident_p();
  if (parsed.isSuccess()) {
    this->ws();
    expr::ExprPtr res = std::make_unique<expr::Identifier>(parsed.get());
    return PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
  } else {
    return PResult<expr::ExprPtr>::error(this->getPos(), "expected identifier");
  }
}

PResult<expr::ExprPtr> ExprParser::expr() {
  // possible space before expr
  ws();
  // parse left expr
  auto node = this->term();
  if (node.isSuccess()) {
    // if it's successful parse the possible space
    ws();
    // check for the operator and make sure it's + or -
    char c = cur();
    while (c == '+' || c == '-') {
      this->consume();
      // again parse possible space and the right expr
      ws();
      auto right = this->term();
      if (right.isSuccess()) {
        switch (c) {
        case '+': {
          expr::ExprPtr res = std::make_unique<expr::BinOp>(
              std::move(node.yield()), std::move(right.yield()),
              expr::Op::PLUS);
          node =
              PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
        }
        case '-': {
          expr::ExprPtr res = std::make_unique<expr::BinOp>(
              std::move(node.yield()), std::move(right.yield()),
              expr::Op::MINUS);
          node =
              PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
        }
        }
        ws();
        c = cur();
      }
    }
    return node;
  }
  return PResult<expr::ExprPtr>::error(this->getPos(), "failed to parse term");
}

PResult<expr::ExprPtr> ExprParser::term() {
  auto node = this->factor();
  if (node.isSuccess()) {
    // if it's successful parse the possible space
    ws();
    // check for the operator and make sure it's * or /
    char c = cur();
    while (c == '*' || c == '/') {
      this->consume();
      // again parse possible space and the right expr
      ws();
      auto right = this->factor();
      if (right.isSuccess()) {
        switch (c) {
        case '*': {
          expr::ExprPtr res = std::make_unique<expr::BinOp>(
              std::move(node.yield()), std::move(right.yield()),
              expr::Op::MULT);
          node =
              PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
        }
        case '/': {
          expr::ExprPtr res = std::make_unique<expr::BinOp>(
              std::move(node.yield()), std::move(right.yield()), expr::Op::DIV);
          node =
              PResult<expr::ExprPtr>::success(std::move(res), this->getPos());
        }
        }
        ws();
        c = cur();
      }
    }
    return node;
  }
  return PResult<expr::ExprPtr>::error(this->getPos(),
                                       "failed to parse factor");
}

PResult<expr::ExprPtr> ExprParser::factor() {
  // save position because this is an alternative parser
  this->ws();
  Position saved = this->getPos();
  auto node = this->integer();
  if (node.isSuccess()) {
    return node;
  }
  setPos(saved);
  node = this->identifier();
  if (node.isSuccess()) {
    return node;
  }
  setPos(saved);
  node = this->group();
  if (node.isSuccess()) {
    return node;
  } else {
    this->setPos(saved);
    return PResult<expr::ExprPtr>::error(this->getPos(),
                                         "failed to parse factor");
  }
}

PResult<expr::ExprPtr> ExprParser::group() {
  this->ws();
  char c = this->peek();
  if (c == '(') {
    this->consume();
    this->ws();
    auto node = this->expr();
    if (node.isSuccess()) {
      this->ws();
      c = this->peek();
      if (c == ')') {
        this->consume();
        return node;
      } else {
        this->setPos(this->getPos());
        return PResult<expr::ExprPtr>::error(this->getPos(), "expected ')'");
      }
    } else {
      this->setPos(this->getPos());
      return PResult<expr::ExprPtr>::error(this->getPos(), "expected expr");
    }
  } else {
    this->setPos(this->getPos());
    return PResult<expr::ExprPtr>::error(this->getPos(), "expected '('");
  }
}
