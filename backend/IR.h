// Copyright msg for cpplint

#ifndef BACKEND_IR_H_
#define BACKEND_IR_H_
#include <iostream>
#include <string>
#include <vector>
#include "utility/memory.h"


namespace cs160 {
namespace intermediate_representation {

class Program;
class StatementNode;

class Register {
 public:
  explicit Register(int v) {
     value_ = std::move(v);
  }
  int GetValue() const { return value_; }
 private:
  int value_;
};

class Operand {
 public:
  explicit Operand(int v) {
     value_ = std::move(v);
  }
  int GetValue() const { return value_; }
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
  explicit StatementNode(std::unique_ptr<Register> target)
                : target_(std::move(target)) {}
  StatementNode(std::unique_ptr<Register> target,
                std::unique_ptr<Instruction> instruction,
                std::unique_ptr<Operand> operand1,
                std::unique_ptr<Operand> operand2,
                std::unique_ptr<StatementNode> next)
                : target_(std::move(target)),
                  instruction_(std::move(instruction)),
                  operand1_(std::move(operand1)),
                  operand2_(std::move(operand2)),
                  next_(std::move(next)) {}
 private:
    std::unique_ptr<Register> target_;
    std::unique_ptr<Instruction> instruction_;
    std::unique_ptr<Operand> operand1_;
    std::unique_ptr<Operand> operand2_;
    std::unique_ptr<StatementNode> next_;
};

}  // namespace intermediate_representation
}  // namespace cs160

#endif  // BACKEND_IR_H_
