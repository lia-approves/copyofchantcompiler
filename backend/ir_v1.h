// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V1_H_
#define BACKEND_IR_V1_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"

using std::stringstream;
using std::endl;

namespace cs160 {
namespace backend {

class Operand {
 public:
    Operand() {}
    virtual ~Operand() {}
    virtual int GetValue() = 0;
    virtual std::string GetName() = 0;
    virtual void PushToAsmSS(stringstream& ss) = 0;
 private:
};

class Register : public Operand {
 public:
  explicit Register(int v) { value_ = (v); }
  ~Register() {}
  int GetValue() { return value_; }
  std::string GetName() { return "t" + std::to_string(value_); }
  void PushToAsmSS(stringstream& ss) {
  // There is nothing to push because it's a register
  }
 private:
  int value_;
};

class Constant : public Operand {
 public:
  explicit Constant(int v) { value_ = (v); }
  ~Constant() {}
  int GetValue() { return value_; }
  std::string GetName() { return std::to_string(value_); }
  void PushToAsmSS(stringstream& ss) {
    ss << "push $" << value_ << endl;
  }
 private:
  int value_;
};

class Instruction {
 public:
    enum Opcode { kAdd, kSubtract, kMultiply, kDivide };
    explicit Instruction(Opcode o) { op_ = (o); }
    ~Instruction() {}
    Opcode GetOpcode() const { return op_; }
    std::string GetName() {
      if (op_ == kAdd) return "add";
      if (op_ == kSubtract) return "subtract";
      if (op_ == kMultiply) return "multiply";
      if (op_ == kDivide) return "divide";
    }
 private:
  Opcode op_;
};

class StatementNode {
 public:
    StatementNode(Register* target,
      Instruction* instruction,
      Operand* operand1,
      Operand* operand2,
      StatementNode* next)
      : target_((target)),
      instruction_((instruction)),
      operand1_((operand1)),
      operand2_((operand2)),
      next_((next)) {}
    ~StatementNode() {
      delete target_;
      delete instruction_;
      delete operand1_;
      delete operand2_;
    }
    Operand& GetOp1() { return *operand1_; }
    Operand& GetOp2() { return *operand2_; }
    Register& GetTarget() { return *target_; }
    Instruction& GetInstruction() { return *instruction_; }
    StatementNode*& GetNext() { return next_; }

 private:
    Register * target_;
    Instruction* instruction_;
    Operand* operand1_;
    Operand* operand2_;
    StatementNode* next_;
};

}  // namespace backend
}  // namespace cs160

#endif  // BACKEND_IR_V1_H_
