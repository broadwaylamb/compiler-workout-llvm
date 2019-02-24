//
//
//  Expr.cpp
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 22/02/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#include "Expr.h"

using namespace compiler_workout;
using namespace llvm;

Expected<num_t> ConstExpr::eval(const State&) const {
  return value();
}

Expected<num_t> VarExpr::eval(const State& state) const {
  const auto it = state.find(name());
  if (it == state.end()) {
    return make_error<StringError>("Undefined variable " + name(),
                                   inconvertibleErrorCode());
  } else {
    return it->getValue();
  }
}

Expected<num_t> BinopExpr::eval(const State& state) const {
  auto lhsEval = lhs().eval(state);
  auto rhsEval = rhs().eval(state);
  if (!lhsEval) {
    return lhsEval.takeError();
  }
  if (!rhsEval) {
    return rhsEval.takeError();
  }
  if (op() == "+") {
    return *lhsEval + *rhsEval;
  } else if (op() == "-") {
    return *lhsEval - *rhsEval;
  } else if (op() == "*") {
    return *lhsEval * *rhsEval;
  } else if (op() == "/") {
    return *lhsEval / *rhsEval;
  } else if (op() == "%") {
    return *lhsEval % *rhsEval;
  } else if (op() == "<") {
    return num_t(*lhsEval < *rhsEval);
  } else if (op() == ">") {
    return num_t(*lhsEval > *rhsEval);
  } else if (op() == "<=") {
    return num_t(*lhsEval <= *rhsEval);
  } else if (op() == ">=") {
    return num_t(*lhsEval >= *rhsEval);
  } else if (op() == "==") {
    return num_t(*lhsEval == *rhsEval);
  } else if (op() == "!=") {
    return num_t(*lhsEval != *rhsEval);
  } else if (op() == "&&") {
    return num_t(bool(*lhsEval) && bool(*rhsEval));
  } else if (op() == "!!") {
    return num_t(bool(*lhsEval) || bool(*rhsEval));
  } else {
    return make_error<StringError>("Undefined binary operator " + op(),
                                   inconvertibleErrorCode());
  }
}

Expr::~Expr() {}
