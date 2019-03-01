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

#include "Stmt.h"

namespace compiler_workout {

struct ASTPrinter {

  virtual void printConstExpr(const ConstExpr& expr) = 0;

  virtual void printVarExpr(const VarExpr& expr) = 0;

  virtual void printBinopExpr(const BinopExpr& expr) = 0;

  virtual void printReadStmt(const ReadStmt& stmt) = 0;

  virtual void printWriteStmt(const WriteStmt& stmt) = 0;

  virtual void printAssignStmt(const AssignStmt& stmt) = 0;

  virtual ~ASTPrinter() {}
};

struct StreamASTPrinter : ASTPrinter {

  StreamASTPrinter(llvm::raw_ostream& stream, bool disableColors = false);

  virtual void printConstExpr(const ConstExpr& expr) override;

  virtual void printVarExpr(const VarExpr& expr) override;

  virtual void printBinopExpr(const BinopExpr& expr) override;

  virtual void printReadStmt(const ReadStmt& stmt) override;

  virtual void printWriteStmt(const WriteStmt& stmt) override;

  virtual void printAssignStmt(const AssignStmt& stmt) override;

private:
  void printPre();

  void printPost(bool indentClosingBrace = false);

private:
  llvm::raw_ostream& output_;
  unsigned depth_;
  bool disableColors_;
};

} // namespace compiler_workout

#endif /* compiler_workout_llvm_ASTPrinter_h */
