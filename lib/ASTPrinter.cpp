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

void StreamASTPrinter::printPre() {
  output_.indent(depth_ * 2);
  WithColor(output_, HighlightColor::Tag, disableColors_) << "(";
}

void StreamASTPrinter::printPost(bool indentClosingBrace) {
  output_.indent(indentClosingBrace ? depth_ * 2 : 0);
  WithColor(output_, HighlightColor::Tag, disableColors_) << ")"
                                                          << "\n";
}

void StreamASTPrinter::printConstExpr(const ConstExpr& expr) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_)
      << "ConstExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "value=" << expr.value();
  printPost();
}

void StreamASTPrinter::printVarExpr(const VarExpr& expr) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "VarExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "name=" << expr.name();
  printPost();
}

void StreamASTPrinter::printBinopExpr(const BinopExpr& expr) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_)
      << "BinopExpr ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "op=" << expr.op() << "\n";
  ++depth_;
  expr.lhs().acceptPrinter(*this);
  expr.rhs().acceptPrinter(*this);
  --depth_;
  printPost(/*indentClosingBrace=*/true);
}

void StreamASTPrinter::printReadStmt(const ReadStmt& stmt) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "ReadStmt ";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "var=" << stmt.varName();
  printPost();
}

void StreamASTPrinter::printWriteStmt(const WriteStmt& stmt) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "WriteStmt"
                                                                 << "\n";
  ++depth_;
  stmt.expr().acceptPrinter(*this);
  --depth_;
  printPost(/*indentClosingBrace=*/true);
}

void StreamASTPrinter::printAssignStmt(const AssignStmt& stmt) {
  printPre();
  WithColor(output_, HighlightColor::Enumerator, disableColors_) << "AssignStmt"
                                                                 << "\n";
  WithColor(output_, HighlightColor::String, disableColors_)
      << "var=" << stmt.varName();
  ++depth_;
  stmt.expr().acceptPrinter(*this);
  --depth_;
  printPost(/*indentClosingBrace=*/true);
}
