#define BOOST_TEST_MODULE "C++ Unit Tests for Foo"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(expr_test)
{
  int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(i == 1);
}
