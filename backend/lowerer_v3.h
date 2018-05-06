// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V3_H_
#define BACKEND_LOWERER_V3_H_

#include <sstream>
#include <string>
#include <vector>
#include "backend/ir_v3.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_3::IntegerExpr;
using cs160::abstract_syntax::version_3::ArithmeticBinaryOperatorExpr;
using cs160::abstract_syntax::version_3::AddExpr;
using cs160::abstract_syntax::version_3::SubtractExpr;
using cs160::abstract_syntax::version_3::MultiplyExpr;
using cs160::abstract_syntax::version_3::DivideExpr;
using cs160::abstract_syntax::version_3::AstNode;
using cs160::abstract_syntax::version_3::AstVisitor;
using cs160::abstract_syntax::version_3::VariableExpr;
using cs160::abstract_syntax::version_3::Assignment;
using cs160::abstract_syntax::version_3::Program;
using cs160::abstract_syntax::version_3::LessThanExpr;
using cs160::abstract_syntax::version_3::LessThanEqualToExpr;
using cs160::abstract_syntax::version_3::GreaterThanExpr;
using cs160::abstract_syntax::version_3::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_3::EqualToExpr;
using cs160::abstract_syntax::version_3::LogicalAndExpr;
using cs160::abstract_syntax::version_3::LogicalOrExpr;
using cs160::abstract_syntax::version_3::LogicalNotExpr;
using cs160::abstract_syntax::version_3::Conditional;
using cs160::abstract_syntax::version_3::Loop;
using cs160::backend::ir::StatementNode;
using cs160::backend::ir::Constant;
using cs160::backend::ir::Operator;
using cs160::backend::ir::Register;
using cs160::backend::ir::Operand;
using cs160::backend::ir::Variable;


namespace cs160 {
  namespace backend {


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

      void VisitIntegerExpr(const IntegerExpr& exp) {
        stack_.push_back(new Constant(exp.value()));
      }

      void VisitAddExpr(const AddExpr& exp) {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        Operand* op1 = stack_.back();
        StatementNode *newtail = new StatementNode(
          new Register(register_number_),
          new Operator(Operator::kAdd),
          op1,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.pop_back();
        stack_.push_back(new Register(register_number_));
        register_number_++;
      }

      void VisitSubtractExpr(const SubtractExpr& exp) {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        Operand* op1 = stack_.back();
        StatementNode *newtail = new StatementNode(
          new Register(register_number_),
          new Operator(Operator::kSubtract),
          op1,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.pop_back();
        stack_.push_back(new Register(register_number_));
        register_number_++;
      }

      void VisitMultiplyExpr(const MultiplyExpr& exp) {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        Operand* op1 = stack_.back();
        StatementNode *newtail = new StatementNode(
          new Register(register_number_),
          new Operator(Operator::kMultiply),
          op1,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.pop_back();
        stack_.push_back(new Register(register_number_));
        register_number_++;
      }

      void VisitDivideExpr(const DivideExpr& exp) {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        Operand* op1 = stack_.back();
        StatementNode *newtail = new StatementNode(
          new Register(register_number_),
          new Operator(Operator::kDivide),
          op1,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.pop_back();
        stack_.push_back(new Register(register_number_));
        register_number_++;
      }

      void VisitVariableExpr(const VariableExpr& exp) {
        stack_.push_back(new Variable(exp.name()));
      }
      void VisitAssignment(const Assignment& assignment) {
        assignment.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        StatementNode *newtail = new StatementNode(
          new Variable(assignment.lhs().name()),
          new Operator(Operator::kAssign),
          nullptr,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.push_back(new Register(register_number_));
      }
      void VisitProgram(const Program& program) {
        for (auto& assignment : program.assignments()) {
          assignment->Visit(this);
        }
        program.arithmetic_exp().Visit(this);
      }

      void VisitLessThanExpr(const LessThanExpr& exp) {}
      void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {}
      void VisitGreaterThanExpr(const GreaterThanExpr& exp) {}
      void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) {}
      void VisitEqualToExpr(const EqualToExpr& exp) {}
      void VisitLogicalAndExpr(const LogicalAndExpr& exp) {}
      void VisitLogicalOrExpr(const LogicalOrExpr& exp) {}
      void VisitLogicalNotExpr(const LogicalNotExpr& exp) {}
      void VisitConditional(const Conditional& conditional) {}
      void VisitLoop(const Loop& loop) {}

      StatementNode* GetIR() { return head_; }
      void AddToEnd(StatementNode* newtail) {
        if (head_ == nullptr && tail_ == nullptr) {
          head_ = newtail;
          tail_ = newtail;
          return;
        }
        tail_->GetNext() = newtail;
        tail_ = tail_->GetNext();
      }

      void PrintIR() {
        StatementNode* itor = head_;
        while (itor != nullptr) {
          itor->Print();
          itor = itor->GetNext();
          std::cout << endl;
        }
      }

    private:
      StatementNode * head_ = nullptr;
      StatementNode* tail_ = nullptr;
      std::vector<Operand*> stack_;
      int register_number_ = 1;
    };
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_LOWERER_V3_H_
