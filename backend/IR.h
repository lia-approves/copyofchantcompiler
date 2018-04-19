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
  // FILL ME IN
};

class Operand {
  // FILL ME IN
};

class Instruction {
 public:
  Instruction();
  enum Opcode { kAdd, kSubtract, kMultiply, kDivide };
  Opcode GetOpcode() const { return op_; }

 private:
  Opcode op_;
    // FILL ME IN
};

Instruction::Instruction() {
  op_ = kAdd;
}

class Program {
 public:
  void Print() {}
 private:
};

class StatementNode {
 public:
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
