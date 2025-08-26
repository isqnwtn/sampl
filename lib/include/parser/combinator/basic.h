#pragma once

#include <functional>
#include "parser/combinator/util.h"

template <typename T> using Parser = std::function<PResult<T>(State)>;

State advance(const State& st, char c);

Parser<char> satisfy(std::function<bool(char)> pred, std::string expected);
Parser<char> char_p(char expected);

// Combine two parsers in sequence
template <typename A, typename B>
Parser<std::pair<A, B>> seq(Parser<A> p1, Parser<B> p2) {
  using T = std::pair<A, B>;
  return [p1, p2](State st) -> PResult<std::pair<A, B>> {
    auto r1 = p1(st);
    if (!r1.value)
      return PResult<T>::Error(r1.state, r1.error);
    auto r2 = p2(r1.state);
    if (!r2.value)
      return PResult<T>::Error(r2.state, r2.error);
    return PResult<T>(std::make_pair(*r1.value, *r2.value), r2.state);
  };
}

template <typename A,typename B>
Parser<std::pair<A,B>> pair(Parser<A> p1, Parser<B> p2){
    using T = std::pair<A,B>;
    return [p1,p2](State st) -> PResult<std::pair<A,B>> {
        auto r1 = char_p('(')(st);
        if(!r1.value) return PResult<T>::Error(r1.state, r1.error);
        auto r2 = p1(r1.state);
        if(!r2.value) return PResult<T>::Error(r2.state, r2.error);
        auto r3 = char_p(',')(r2.state);
        if(!r3.value) return PResult<T>::Error(r3.state, r3.error);
        auto r4 = p2(r3.state);
        if(!r4.value) return PResult<T>::Error(r4.state, r4.error);
        auto r5 = char_p(')')(r4.state);
        if(!r5.value) return PResult<T>::Error(r5.state, r5.error);
        return PResult<T>(std::make_pair(*r2.value, *r4.value), r5.state);
    };
}
