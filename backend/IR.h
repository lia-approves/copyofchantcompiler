// Copyright msg for cpplint

#ifndef BACKEND_IR_H_
#define BACKEND_IR_H_
#include <iostream>
#include <string>
#include <vector>
#include "../utility/memory.h"


namespace cs160 {
namespace intermediate_representation {

class Program;
class StatementNode;
class OperandBase {
 public:
  OperandBase() {}
  virtual ~OperandBase() {}
  virtual int GetValue() const { return 0; }
  virtual std::string GetName() const { return "0"; }
 private:
};

class Register : public OperandBase {
 public:
  Register() {
    value_ = 1;
  }
  explicit Register(int v) {
     value_ = std::move(v);
  }
  int GetValue() const { return value_; }
  std::string GetName() const {return "t" + std::to_string(value_); }
 private:
  int value_;
};

class Operand : public OperandBase{
 public:
  explicit Operand(int v) {
     value_ = std::move(v);
  }
  ~Operand() {}
  int GetValue() const { return value_; }
  std::string GetName() const { return std::to_string(value_); }

 private:
  int value_;
};

class Instruction {
 public:
  enum Opcode { kAdd, kSubtract, kMultiply, kDivide };
  explicit Instruction(Opcode o) {
    op_ = std::move(o);
  }
  Opcode GetOpcode() const { return op_; }
  std::string GetName() const {
    if (op_ == kAdd) return "add";
    if (op_ == kSubtract) return "subtract";
    if (op_ == kMultiply) return "multiply";
    if (op_ == kDivide) return "divide";
  }
 private:
  Opcode op_;
};


class Program {
 public:
  void Print() {}
 private:
};

class StatementNode {
 public:
  StatementNode() {}
  StatementNode(Register* target,
                Instruction* instruction,
                OperandBase* operand1,
                OperandBase* operand2,
                StatementNode* next)
                : target_((target)),
                  instruction_((instruction)),
                  operand1_((operand1)),
                  operand2_((operand2)),
                  next_((next)) {}
  OperandBase& GetOp1() { return *operand1_; }
  OperandBase& GetOp2() { return *operand2_; }
  Register& GetTarget() { return *target_; }
  Instruction& GetInstruction() { return *instruction_; }
  StatementNode*& GetNext() { return next_; }

 private:
    Register* target_;
    Instruction* instruction_;
    OperandBase* operand1_;
    OperandBase* operand2_;
    StatementNode* next_;
};

}  // namespace intermediate_representation
}  // namespace cs160

#endif  // BACKEND_IR_H_
