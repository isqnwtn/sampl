#include "ast/statement.h"
#include "parser/statement.h"
#include "parser/util.h"
#include <memory>

PResult<stmt::StmtPtr> StmtParser::parseStatement() {
    this->ws();
    // save position
    auto saved = this->getPos();
    // try to parse assignment
    auto res = this->parseAssignment();
    if (res.isSuccess()) {
        return res;
    }
    // if it fails fall back to old position
    this->setPos(saved);
    // try to parse return
    res = this->parseReturn();
    if (res.isSuccess()) {
        return res;
    }
    return PResult<stmt::StmtPtr>::error(saved, "Expected statement");
}

PResult<stmt::StmtPtr> StmtParser::parseAssignment() {
  this->ws();
  auto name = ident_p();
  if (name.isError()) {
    return PResult<stmt::StmtPtr>::error(this->getPos(), "Expected identifier");
  }
  this->ws();

  if (this->cur() == '=') {
    this->consume();
    this->ws();
    auto expr = this->expr();
    if (expr.isError()) {
      return PResult<stmt::StmtPtr>::error(this->getPos(),
                                           "Expected expression");
    }
    stmt::StmtPtr res =
        std::make_unique<stmt::Assignment>(name.get(), expr.yield());
    return PResult<stmt::StmtPtr>::success(std::move(res), this->getPos());
  }

  return PResult<stmt::StmtPtr>(this->getPos(), "Expected '='");
}

PResult<stmt::StmtPtr> StmtParser::parseReturn() {
  this->ws();
  auto r_token = this->pstr("return");
  if (r_token.isError()) {
    return PResult<stmt::StmtPtr>::error(this->getPos(), "Expected 'return'");
  }
  this->ws();
  auto expr = this->expr();
  if (expr.isError()) {
    return PResult<stmt::StmtPtr>::error(this->getPos(),
                                         "Expected expression");
  }
  stmt::StmtPtr res = std::make_unique<stmt::Return>(expr.yield());
  return PResult<stmt::StmtPtr>::success(std::move(res), this->getPos());
}
