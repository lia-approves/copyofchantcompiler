// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V4_H_
#define BACKEND_LOWERER_V4_H_

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v4.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v4.h"


using cs160::abstract_syntax::version_4::IntegerExpr;
using cs160::abstract_syntax::version_4::ArithmeticBinaryOperatorExpr;
using cs160::abstract_syntax::version_4::AddExpr;
using cs160::abstract_syntax::version_4::SubtractExpr;
using cs160::abstract_syntax::version_4::MultiplyExpr;
using cs160::abstract_syntax::version_4::DivideExpr;
using cs160::abstract_syntax::version_4::AstNode;
using cs160::abstract_syntax::version_4::AstVisitor;
using cs160::abstract_syntax::version_4::VariableExpr;
using cs160::abstract_syntax::version_4::Assignment;
using cs160::abstract_syntax::version_4::Program;
using cs160::abstract_syntax::version_4::LessThanExpr;
using cs160::abstract_syntax::version_4::LessThanEqualToExpr;
using cs160::abstract_syntax::version_4::GreaterThanExpr;
using cs160::abstract_syntax::version_4::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_4::EqualToExpr;
using cs160::abstract_syntax::version_4::LogicalAndExpr;
using cs160::abstract_syntax::version_4::LogicalOrExpr;
using cs160::abstract_syntax::version_4::LogicalNotExpr;
using cs160::abstract_syntax::version_4::Conditional;
using cs160::abstract_syntax::version_4::Loop;
using cs160::abstract_syntax::version_4::FunctionCall;
using cs160::abstract_syntax::version_4::FunctionDef;


using cs160::backend::StatementNode;
using cs160::backend::Constant;
using cs160::backend::Label;
using cs160::backend::Operator;
using cs160::backend::Register;
using cs160::backend::Operand;
using cs160::backend::Variable;
using std::cout;


namespace cs160 {
namespace backend {
class CountVisitor : public AstVisitor {
 public:
  void VisitIntegerExpr(const IntegerExpr& exp) override;

  void VisitVariableExpr(const VariableExpr& exp) override;

  void VisitAddExpr(const AddExpr& exp) override;

  void VisitSubtractExpr(const SubtractExpr& exp) override;

  void VisitMultiplyExpr(const MultiplyExpr& exp) override;

  void VisitDivideExpr(const DivideExpr& exp) override;

  void VisitLessThanExpr(const LessThanExpr& exp) override;

  void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) override;

  void VisitGreaterThanExpr(const GreaterThanExpr& exp) override;

  void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) override;
  void VisitEqualToExpr(const EqualToExpr& exp) override;

  void VisitLogicalAndExpr(const LogicalAndExpr& exp) override;

  void VisitLogicalOrExpr(const LogicalOrExpr& exp) override;

  void VisitLogicalNotExpr(const LogicalNotExpr& exp) override;

  void VisitAssignment(const Assignment& assignment) override;

  void VisitConditional(const Conditional& conditional) override;

  void VisitLoop(const Loop& loop) override;

  void VisitProgram(const Program& program) override;
  void VisitFunctionCall(const FunctionCall& call) override;

  void VisitFunctionDef(const FunctionDef& def) override;

  void ScanningParams(bool scanningParams);
  int LocalVars() { return localVariables_.size(); }
  int ParamVars() { return paramVariables_.size(); }

 private:
  bool scanningParams_ = false;
  std::vector<string> paramVariables_;
  std::vector<string> localVariables_;
};
class IrGenVisitor : public AstVisitor {
 public:
  IrGenVisitor() {}
  ~IrGenVisitor() {
    StatementNode* tobe_deleted = head_;
    while (tobe_deleted != nullptr) {
      delete tobe_deleted;
      tobe_deleted = tobe_deleted->GetNext();
    }
  }

  void VisitAddExpr(const AddExpr& exp);

  void VisitSubtractExpr(const SubtractExpr& exp);

  void VisitMultiplyExpr(const MultiplyExpr& exp);

  void VisitDivideExpr(const DivideExpr& exp);
  void VisitIntegerExpr(const IntegerExpr& exp);
  void VisitVariableExpr(const VariableExpr& exp);
  void VisitAssignment(const Assignment& assignment);
  void VisitProgram(const Program& program);
  void VisitFunctionCall(const FunctionCall& call) override;

  void VisitFunctionDef(const FunctionDef& def) override;

  void VisitLessThanExpr(const LessThanExpr& exp);
  void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp);
  void VisitGreaterThanExpr(const GreaterThanExpr& exp) ;
  void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp);
  void VisitEqualToExpr(const EqualToExpr& exp);
  void VisitLogicalAndExpr(const LogicalAndExpr& exp);
  void VisitLogicalOrExpr(const LogicalOrExpr& exp);
  void VisitLogicalNotExpr(const LogicalNotExpr& exp);
  void VisitConditional(const Conditional& conditional);
  void VisitLoop(const Loop& loop);

  StatementNode* GetIR() { return head_; }
  void AddToEnd(StatementNode* newtail);

  void PrintIR();

  int NumberOfStatements();
  int NumberOfMainVars() { return mainVars_; }

 private:
  StatementNode * head_ = nullptr;
  StatementNode* tail_ = nullptr;
  int labelNum_ = 0;
  int register_number_ = 1;
  std::vector<Operand*> stack_;
  int mainVars_ = 0;
  std::vector<string> paramVariables_;
  std::vector<string> localVariables_;
  bool scanningParams_ = false;
};

}  // namespace backend
}  // namespace cs160

#endif  // BACKEND_LOWERER_V4_H_
