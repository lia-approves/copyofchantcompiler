// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V2_H_
#define BACKEND_LOWERER_V2_H_

#include <sstream>
#include <string>
#include <vector>
#include "backend/ir_v2.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v2.h"

using cs160::abstract_syntax::version_2::IntegerExpr;
using cs160::abstract_syntax::version_2::BinaryOperatorExpr;
using cs160::abstract_syntax::version_2::AddExpr;
using cs160::abstract_syntax::version_2::SubtractExpr;
using cs160::abstract_syntax::version_2::MultiplyExpr;
using cs160::abstract_syntax::version_2::DivideExpr;
using cs160::abstract_syntax::version_2::AstNode;
using cs160::abstract_syntax::version_2::AstVisitor;
using cs160::abstract_syntax::version_2::VariableExpr;
using cs160::abstract_syntax::version_2::Assignment;
using cs160::abstract_syntax::version_2::Program;
using cs160::backend::StatementNode;
using cs160::backend::Constant;
using cs160::backend::Operator;
using cs160::backend::Register;
using cs160::backend::Operand;
using cs160::backend::Variable;



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

  void VisitBinaryOperatorExpr(const BinaryOperatorExpr& exp) {}

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

#endif  // BACKEND_LOWERER_V2_H_
