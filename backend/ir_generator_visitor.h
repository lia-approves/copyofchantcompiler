/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef BACKEND_IR_GENERATOR_VISITOR_V1_H_
#define BACKEND_IR_GENERATOR_VISITOR_V1_H_

#include "abstract_syntax/abstract_syntax_tree_v1.h"
#include "backend/IR.h"
#include "utility/memory.h"


#include <sstream>
#include <string>
#include <vector>


namespace cs160 {
namespace abstract_syntax {
namespace version_1 {

  using cs160::intermediate_representation::Instruction;
  using cs160::intermediate_representation::Operand;
  using cs160::intermediate_representation::Program;
  using cs160::intermediate_representation::Register;
  using cs160::intermediate_representation::StatementNode;
  using cs160::intermediate_representation::OperandBase;

  struct OperandBaseNode {    //need to convert linked list to vector array
    OperandBaseNode(OperandBase* opInit, OperandBaseNode* init_next)
    {
      data_ = opInit, next_ = init_next;
    }
    OperandBase* data_;
    OperandBaseNode* next_;
  };

 class IrGenVisitor : public AstVisitor {
  public:
   IrGenVisitor() {}
   ~IrGenVisitor() {}

  void VisitIntegerExpr(const IntegerExpr& exp) {
    stack_.push_back(new Operand(exp.value()));
  }

  void VisitBinaryOperatorExpr(const BinaryOperatorExpr& exp) {}

  void VisitAddExpr(const AddExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    OperandBase* op2 = stack_.back();
    stack_.pop_back();
    OperandBase* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(new Register(register_number_), new Instruction(Instruction::kAdd), op1, op2, nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }
  void VisitSubtractExpr(const SubtractExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    OperandBase* op2 = stack_.back();
    stack_.pop_back();
    OperandBase* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(new Register(register_number_), new Instruction(Instruction::kSubtract), op1, op2, nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  void VisitMultiplyExpr(const MultiplyExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    OperandBase* op2 = stack_.back();
    stack_.pop_back();
    OperandBase* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(new Register(register_number_), new Instruction(Instruction::kMultiply), op1, op2, nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  void VisitDivideExpr(const DivideExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    OperandBase* op2 = stack_.back();
    stack_.pop_back();
    OperandBase* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(new Register(register_number_), new Instruction(Instruction::kDivide), op1, op2, nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  StatementNode* GetIR() {  return head_; }
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
  StatementNode* head_ = nullptr;
  StatementNode* tail_ = nullptr;
  std::vector<OperandBase*> stack_;
  int register_number_ = 1;
};

}  // namespace version_1
}  // namespace abstract_syntax
}  // namespace cs160

#endif  // BACKEND_IR_GENERATOR_VISITOR_V1_H_
