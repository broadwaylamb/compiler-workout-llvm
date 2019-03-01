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

#include "ASTPrinter.h"

using namespace compiler_workout;
using namespace llvm;

void Expr::dump(raw_ostream& stream) const {
  StreamASTPrinter printer(stream);
  acceptPrinter(printer);
}

Expected<num_t> ConstExpr::eval(const State&) const {
  return value();
}

void ConstExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printConstExpr(*this);
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

void VarExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printVarExpr(*this);
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

void BinopExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printBinopExpr(*this);
}
