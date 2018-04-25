// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_GENERATOR_AST_VISITOR_V1_H_
#define BACKEND_IR_GENERATOR_AST_VISITOR_V1_H_

#include <sstream>
#include <string>
#include <vector>
#include "abstract_syntax/abstract_syntax_tree_v1.h"
#include "backend/intermediate_representation_v1.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::BinaryOperatorExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::abstract_syntax::version_1::AstNode;
using cs160::abstract_syntax::version_1::AstVisitor;

namespace cs160 {
namespace backend {

class IrGenVisitor : public AstVisitor {
 public:
    IrGenVisitor() {}
    ~IrGenVisitor() {
      while (head_ != nullptr) {
        StatementNode* next = head_->GetNext();
        delete head_;
        head_ = next;
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
        new Instruction(Instruction::kAdd),
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
        new Instruction(Instruction::kSubtract),
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
        new Instruction(Instruction::kMultiply),
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
        new Instruction(Instruction::kDivide),
        op1,
        op2,
        nullptr);
      AddToEnd(newtail);
      stack_.pop_back();
      stack_.push_back(new Register(register_number_));
      register_number_++;
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
        std::cout << itor->GetTarget().GetName() << " = ";
        std::cout << itor->GetOp1().GetName() << " ";
        std::cout << itor->GetInstruction().GetName() << " ";
        std::cout << itor->GetOp2().GetName() << " ";
        std::cout << std::endl;
        itor = itor->GetNext();
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

#endif  // BACKEND_IR_GENERATOR_AST_VISITOR_V1_H_
