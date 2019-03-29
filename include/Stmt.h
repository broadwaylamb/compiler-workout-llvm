//
//
//  Stmt.h
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 01/03/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#ifndef compiler_workout_llvm_Stmt_h
#define compiler_workout_llvm_Stmt_h

#include "Expr.h"

#include "llvm/Support/MemoryBuffer.h"

#include <istream>

namespace compiler_workout {

struct ASTPrinter;

struct Stmt {

  /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
  enum StmtKind { StmtKind_Read, StmtKind_Write, StmtKind_Assign };

  Stmt(StmtKind kind) : kind_(kind) {}

  virtual void acceptPrinter(ASTPrinter& printer) const = 0;

  void dump(llvm::raw_ostream& stream = llvm::outs()) const;

  StmtKind kind() const { return kind_; }

  virtual ~Stmt() {}

private:
  const StmtKind kind_;
};

struct ReadStmt : Stmt {

  ReadStmt(llvm::StringRef varName) : Stmt(StmtKind_Read), varName_(varName) {}

  llvm::StringRef varName() const { return varName_; }

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const std::string varName_;

public:
  static bool classof(const Stmt* stmt) {
    return stmt->kind() == StmtKind_Read;
  }
};

struct WriteStmt : Stmt {

  WriteStmt(std::unique_ptr<const Expr> expr)
      : Stmt(StmtKind_Write), expr_(std::move(expr)) {}

  const Expr& expr() const { return *expr_; }

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const std::unique_ptr<const Expr> expr_;

public:
  static bool classof(const Stmt* stmt) {
    return stmt->kind() == StmtKind_Write;
  }
};

struct AssignStmt : Stmt {

  AssignStmt(llvm::StringRef varName, std::unique_ptr<const Expr> expr)
      : Stmt(StmtKind_Assign), varName_(varName), expr_(std::move(expr)) {}

  llvm::StringRef varName() const { return varName_; }

  const Expr& expr() const { return *expr_; }

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const std::string varName_;
  const std::unique_ptr<const Expr> expr_;

public:
  static bool classof(const Stmt* stmt) {
    return stmt->kind() == StmtKind_Assign;
  }
};

} // namespace compiler_workout

#endif /* compiler_workout_llvm_Stmt_h */
