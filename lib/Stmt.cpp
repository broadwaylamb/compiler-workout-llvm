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

Error ReadStmt::eval(State& state,
                     std::istream& input,
                     [[maybe_unused]] std::ostream& output) const {

  num_t number;
  input >> number;
  state.try_emplace(varName(), number);

  return Error::success();
}

void ReadStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printReadStmt(*this);
}

Error WriteStmt::eval(State& state,
                      [[maybe_unused]] std::istream& input,
                      std::ostream& output) const {

  if (auto result = expr().eval(state)) {
    output << *result;
    return Error::success();
  } else {
    return result.takeError();
  }
}

void WriteStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printWriteStmt(*this);
}

Error AssignStmt::eval(State& state,
                       [[maybe_unused]] std::istream& input,
                       [[maybe_unused]] std::ostream& output) const {
  if (auto result = expr().eval(state)) {
    state.try_emplace(varName(), *result);
    return Error::success();
  } else {
    return result.takeError();
  }
}

void AssignStmt::acceptPrinter(ASTPrinter& printer) const {
  printer.printAssignStmt(*this);
}
