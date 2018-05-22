// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V5_H_
#define BACKEND_LOWERER_V5_H_

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v5.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v5.h"
#include <algorithm>




using cs160::abstract_syntax::version_5::AstVisitor;
using cs160::abstract_syntax::version_5::ArithmeticExpr;
using cs160::abstract_syntax::version_5::Assignable;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::Dereference;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::LessThanEqualToExpr;
using cs160::abstract_syntax::version_5::GreaterThanExpr;
using cs160::abstract_syntax::version_5::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_5::EqualToExpr;
using cs160::abstract_syntax::version_5::LogicalAndExpr;
using cs160::abstract_syntax::version_5::LogicalOrExpr;
using cs160::abstract_syntax::version_5::LogicalNotExpr;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::AssignmentFromNewTuple;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::Loop;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;
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
    class VarCountVisitor : public AstVisitor {
    public:
      VarCountVisitor() {}
      ~VarCountVisitor() {}
      void VisitIntegerExpr(const IntegerExpr& exp) override;
      void VisitVariableExpr(const VariableExpr& exp) override;

      void VisitDereference(const Dereference& exp) override;

      void VisitAssignmentFromArithExp(
        const AssignmentFromArithExp& assignment) override;

      void VisitAssignmentFromNewTuple(
        const AssignmentFromNewTuple& assignment) override;

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

      void VisitConditional(const Conditional& conditional) override;

      void VisitLoop(const Loop& loop) override;

      void VisitProgram(const Program& program) override;
      void VisitFunctionCall(const FunctionCall& call) override;

      void VisitFunctionDef(const FunctionDef& def) override;
      void ScanningParams(bool scanningParams);
      int LocalVars();
      int ParamVars();
    private:
      bool scanningParams_ = false;
      std::vector<string> paramVariables_;
      std::vector<string> localVariables_;
      int count_ = 0;//dummy from transfering v5
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
      void VisitIntegerExpr(const IntegerExpr& exp) override;
      void VisitVariableExpr(const VariableExpr& exp) override;
      void VisitDereference(const Dereference& exp) override;
      void VisitAssignmentFromArithExp(const AssignmentFromArithExp& assignment) override;
      void VisitAssignmentFromNewTuple(const AssignmentFromNewTuple& assignment) override;
      void VisitAddExpr(const AddExpr& exp) override;
      void VisitSubtractExpr(const SubtractExpr& exp) override;
      void VisitMultiplyExpr(const MultiplyExpr& exp) override;
      void VisitDivideExpr(const DivideExpr& exp) override;
      void VisitProgram(const Program& program) override;
      void VisitFunctionCall(const FunctionCall& call) override;
      void VisitFunctionDef(const FunctionDef& def) override;
      void VisitLessThanExpr(const LessThanExpr& exp) override;
      void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) override;
      void VisitGreaterThanExpr(const GreaterThanExpr& exp) override;
      void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) override;
      void VisitEqualToExpr(const EqualToExpr& exp) override;
      void VisitLogicalAndExpr(const LogicalAndExpr& exp) override;
      void VisitLogicalOrExpr(const LogicalOrExpr& exp) override;
      void VisitLogicalNotExpr(const LogicalNotExpr& exp) override;
      void VisitConditional(const Conditional& conditional) override;
      void VisitLoop(const Loop& loop) override;
      StatementNode* GetIR() { return head_; }
      void AddToEnd(StatementNode* newtail);
      void PrintIR();
      int NumberOfStatements();
      int NumberOfMainVars() { return mainVars_; }
    private:

      StatementNode * head_ = nullptr;
      StatementNode* tail_ = nullptr;
      int labelNum_ = 1;
      int register_number_ = 1;
      std::vector<Operand*> stack_;
      int mainVars_ = 0;
      std::vector<string> paramVariables_;
      std::vector<string> localVariables_;
      bool scanningParams_ = false;

    };

  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_LOWERER_V5_H_
