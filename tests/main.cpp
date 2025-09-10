#define BOOST_TEST_MODULE "C++ Unit Tests for Foo"
#include "parser/expr.h"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(parser_tests)

BOOST_AUTO_TEST_CASE(integer_test) {
  ExprParser p("123");
  auto res = p.integer();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::IntValue *>(res.get().get());
  BOOST_TEST(val->getValue() == 123);
}

BOOST_AUTO_TEST_CASE(identifier_test) {
  ExprParser p("abc");
  auto res = p.identifier();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::Identifier *>(res.get().get());
  BOOST_TEST(val->getIdent() == "abc");
}

BOOST_AUTO_TEST_CASE(group_test) {
  ExprParser p("(123)");
  auto res = p.group();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::GroupExpr *>(res.get().get());
  auto inner = dynamic_cast<expr::IntValue *>(val->getExpr().get());
  BOOST_TEST(inner->getValue() == 123);
}

BOOST_AUTO_TEST_CASE(term_test) {
  ExprParser p("1 * 2");
  auto res = p.term();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::BinOp *>(res.get().get());
  auto left = dynamic_cast<expr::IntValue *>(val->getLeft().get());
  auto right = dynamic_cast<expr::IntValue *>(val->getRight().get());
  BOOST_TEST(left->getValue() == 1);
  BOOST_TEST(right->getValue() == 2);
}

BOOST_AUTO_TEST_CASE(factor_test) {
  ExprParser p("123");
  auto res = p.factor();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::IntValue *>(res.get().get());
  BOOST_TEST(val->getValue() == 123);
}

BOOST_AUTO_TEST_CASE(expr_test) {
  ExprParser p("1 + 2");
  auto res = p.expr();
  BOOST_TEST(res.isSuccess());
  auto val = dynamic_cast<expr::BinOp *>(res.get().get());
  auto left = dynamic_cast<expr::IntValue *>(val->getLeft().get());
  auto right = dynamic_cast<expr::IntValue *>(val->getRight().get());
  BOOST_TEST(left->getValue() == 1);
  BOOST_TEST(right->getValue() == 2);
}

BOOST_AUTO_TEST_SUITE_END()
