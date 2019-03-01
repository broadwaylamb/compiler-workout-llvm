//
//
//  ASTPrinter.h
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 01/03/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#ifndef compiler_workout_llvm_ASTPrinter_h
#define compiler_workout_llvm_ASTPrinter_h

#include "Expr.h"

namespace compiler_workout {

struct ASTPrinter {

  virtual void printConstExpr(const ConstExpr& expr) = 0;

  virtual void printVarExpr(const VarExpr& expr) = 0;

  virtual void printBinopExpr(const BinopExpr& expr) = 0;

  virtual ~ASTPrinter() {}
};

struct StreamASTPrinter : ASTPrinter {

  StreamASTPrinter(llvm::raw_ostream& stream, bool disableColors = false);

  virtual void printConstExpr(const ConstExpr& expr) override;

  virtual void printVarExpr(const VarExpr& expr) override;

  virtual void printBinopExpr(const BinopExpr& expr) override;

private:
  void printExprPre();

  void printExprPost(bool indentClosingBrace = false);

private:
  llvm::raw_ostream& output_;
  unsigned depth_;
  bool disableColors_;
};

} // namespace compiler_workout

#endif /* compiler_workout_llvm_ASTPrinter_h */
