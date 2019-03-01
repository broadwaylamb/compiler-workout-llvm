//
//
//  ASTPrinter.cpp
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 01/03/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#include "ASTPrinter.h"

#include "llvm/Support/WithColor.h"

using namespace llvm;
using namespace compiler_workout;

StreamASTPrinter::StreamASTPrinter(raw_ostream& stream, bool disableColors)
    : output_(stream), depth_(0), disableColors_(disableColors) {}

void StreamASTPrinter::printExprPre() {
  output_.indent(depth_ * 2);
  WithColor(output_, HighlightColor::Tag, disableColors_) << "(";
}

void StreamASTPrinter::printExprPost(bool indentClosingBrace) {
  output_.indent(indentClosingBrace ? depth_ * 2 : 0);
  WithColor(output_, HighlightColor::Tag, disableColors_) << ")"
                                                          << "\n";
}

void StreamASTPrinter::printConstExpr(const ConstExpr& expr) {
  printExprPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_)
      << "ConstExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "value=" << expr.value();
  printExprPost();
}

void StreamASTPrinter::printVarExpr(const VarExpr& expr) {
  printExprPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "VarExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "name=" << expr.name();
  printExprPost();
}

void StreamASTPrinter::printBinopExpr(const BinopExpr& expr) {
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
