#pragma once
#include "ast/statement.h"
#include "parser/basic.h"
#include "parser/expr.h"
#include "parser/util.h"
#include <string>

class StmtParser : ExprParser {
    public:
    StmtParser(State& state) : ExprParser(state) {}
    StmtParser(const std::string& input) : ExprParser(input) {}
    ~StmtParser() {}

    // parser functions
    PResult<stmt::StmtPtr> parseStatement();
    PResult<stmt::StmtPtr> parseAssignment();
    PResult<stmt::StmtPtr> parseReturn();
};
