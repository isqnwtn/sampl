#pragma once

#include "ast/expr.h"
#include "parser/basic.h"
#include "parser/util.h"

class ExprParser : public Parser {
public:
  // Constructors and destructors
  ExprParser(State &state) : Parser(state) {}
  ExprParser(const std::string &input) : Parser(input) {}
  ~ExprParser() {}

  // Parsers
  PResult<expr::ExprPtr> expr();
  PResult<expr::ExprPtr> integer();
  PResult<expr::ExprPtr> identifier();
  PResult<expr::ExprPtr> group();
  PResult<expr::ExprPtr> term();
  PResult<expr::ExprPtr> factor();
};
