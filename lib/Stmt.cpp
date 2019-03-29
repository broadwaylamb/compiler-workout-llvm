//
//
//  Stmt.cpp
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 01/03/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#include "Stmt.h"

#include "ASTPrinter.h"

using namespace compiler_workout;
using namespace llvm;

void Stmt::dump(raw_ostream& stream) const {
  StreamASTPrinter printer(stream);
  acceptPrinter(printer);
}

void ReadStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printReadStmt(*this);
}

void WriteStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printWriteStmt(*this);
}

void AssignStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printAssignStmt(*this);
}
