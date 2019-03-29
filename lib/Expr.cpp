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

void ConstExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printConstExpr(*this);
}

void VarExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printVarExpr(*this);
}

void BinopExpr::acceptPrinter(ASTPrinter& printer) const {
  printer.printBinopExpr(*this);
}
