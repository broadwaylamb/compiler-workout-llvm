//
//
//  Expr.h
//  compiler-workout-llvm
//
//  Created by Sergej Jaskiewicz on 22/02/2019
//
//  GitHub
//  https://github.com/broadwaylamb/compiler-workout-llvm
//

#ifndef compiler_workout_llvm_Expr_h
#define compiler_workout_llvm_Expr_h

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>

namespace compiler_workout {

using num_t = int64_t;

using State = llvm::StringMap<num_t>;

struct ASTPrinter;

struct Expr {

  /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
  enum ExprKind { ExprKind_Const, ExprKind_Var, ExprKind_Binop };

  Expr(ExprKind kind) : kind_(kind) {}

  virtual llvm::Expected<num_t> eval(const State& state) const = 0;

  virtual void acceptPrinter(ASTPrinter& printer) const = 0;

  void dump(llvm::raw_ostream& stream = llvm::outs()) const;

  ExprKind kind() const { return kind_; }

  virtual ~Expr() {}

private:
  const ExprKind kind_;
};

struct ConstExpr : Expr {

  ConstExpr(num_t value) : Expr(ExprKind_Const), value_(value) {}

  num_t value() const { return value_; }

  virtual llvm::Expected<num_t> eval(const State& state) const override;

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const num_t value_;

public:
  static bool classof(const Expr* expr) {
    return expr->kind() == ExprKind_Const;
  }
};

struct VarExpr : Expr {

  VarExpr(llvm::StringRef name) : Expr(ExprKind_Var), name_(name) {}

  llvm::StringRef name() const { return name_; }

  virtual llvm::Expected<num_t> eval(const State& state) const override;

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const llvm::StringRef name_;

public:
  static bool classof(const Expr* expr) { return expr->kind() == ExprKind_Var; }
};

struct BinopExpr : Expr {

  BinopExpr(llvm::StringRef op,
            std::unique_ptr<const Expr> lhs,
            std::unique_ptr<const Expr> rhs)
      : Expr(ExprKind_Binop), op_(op), lhs_(std::move(lhs)),
        rhs_(std::move(rhs)) {}

  llvm::StringRef op() const { return op_; }

  const Expr& lhs() const { return *lhs_; }

  const Expr& rhs() const { return *rhs_; }

  virtual llvm::Expected<num_t> eval(const State& state) const override;

  virtual void acceptPrinter(ASTPrinter& printer) const override;

private:
  const llvm::StringRef op_;
  const std::unique_ptr<const Expr> lhs_;
  const std::unique_ptr<const Expr> rhs_;

public:
  static bool classof(const Expr* expr) {
    return expr->kind() == ExprKind_Binop;
  }
};

} // namespace compiler_workout

#endif /* compiler_workout_llvm_Expr_h */
