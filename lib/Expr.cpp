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

#include "llvm/Support/WithColor.h"

using namespace compiler_workout;
using namespace llvm;

void Expr::dump(raw_ostream& stream) const {
  StreamExprPrinter printer(stream);
  acceptPrinter(printer);
}

Expected<num_t> ConstExpr::eval(const State&) const {
  return value();
}

void ConstExpr::acceptPrinter(ExprPrinter& printer) const {
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

void VarExpr::acceptPrinter(compiler_workout::ExprPrinter& printer) const {
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

void BinopExpr::acceptPrinter(compiler_workout::ExprPrinter& printer) const {
  printer.printBinopExpr(*this);
}

StreamExprPrinter::StreamExprPrinter(raw_ostream& stream, bool disableColors)
    : output_(stream), depth_(0), disableColors_(disableColors) {}

void StreamExprPrinter::printExprPre() {
  output_.indent(depth_ * 2);
  WithColor(output_, HighlightColor::Tag, disableColors_) << "(";
}

void StreamExprPrinter::printExprPost(bool indentClosingBrace) {
  output_.indent(indentClosingBrace ? depth_ * 2 : 0);
  WithColor(output_, HighlightColor::Tag, disableColors_) << ")"
                                                          << "\n";
}

void StreamExprPrinter::printConstExpr(const ConstExpr& expr) {
  printExprPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_)
      << "ConstExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "value=" << expr.value();
  printExprPost();
}

void StreamExprPrinter::printVarExpr(const VarExpr& expr) {
  printExprPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "VarExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "name=" << expr.name();
  printExprPost();
}

void StreamExprPrinter::printBinopExpr(const BinopExpr& expr) {
  printExprPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_)
      << "BinopExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "op=" << expr.op() << "\n";
  ++depth_;
  expr.lhs().acceptPrinter(*this);
  expr.rhs().acceptPrinter(*this);
  --depth_;
  printExprPost(/*indentClosingBrace=*/true);
}
