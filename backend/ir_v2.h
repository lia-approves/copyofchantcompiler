// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V2_H_
#define BACKEND_IR_V2_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"

using std::stringstream;
using std::endl;

namespace cs160 {
  namespace backend {
    namespace ir {

      class Operand { //abstract class for operand can be constant(integer), variable or register
      public:
        Operand() {}
        virtual ~Operand() {}
        virtual int GetValue() = 0;
        virtual std::string GetName() = 0;
        virtual void PushToAsmSS(stringstream& ss) = 0; // function for asm generator
      private:
      };

      class Register : public Operand { // t1, t2 ,etc
      public:
        explicit Register(int v) { value_ = (v); }
        ~Register() {}
        int GetValue() { return value_; }
        std::string GetName() { return "t" + std::to_string(value_); }
        void PushToAsmSS(stringstream& ss) {  // function for asm generator
                                              // There is nothing to push because it's a register
        }
      private:
        int value_;
      };
      class Variable : public Operand { // bob, a, b, height, etc
      public:
        explicit Variable(std::string s) { name_ = (s); }
        ~Variable() {}
        int GetValue() { return 0; } //dummy return
        std::string GetName() { return name_; }
        void PushToAsmSS(stringstream& ss) {  // function for asm generator
                                              // There is nothing to push because it's a variable
        }
      private:
        std::string name_;
      };

      class Constant : public Operand { // integer value 3, 8, 6 etc
      public:
        explicit Constant(int v) { value_ = (v); }
        ~Constant() {}
        int GetValue() { return value_; }
        std::string GetName() { return std::to_string(value_); }
        void PushToAsmSS(stringstream& ss) { // function for asm generator
          ss << "push $" << value_ << endl;
        }
      private:
        int value_;
      };

      class Operator { // assign, add multiply, etc
      public:
        enum Opcode { kAdd, kSubtract, kMultiply, kDivide, kAssign };
        explicit Operator(Opcode o) { op_ = (o); }
        ~Operator() {}
        Opcode GetOpcode() const { return op_; }
        std::string GetName() {
          if (op_ == kAdd) return "add";
          if (op_ == kSubtract) return "subtract";
          if (op_ == kMultiply) return "multiply";
          if (op_ == kDivide) return "divide";
          if (op_ == kAssign) return "assign";
        }
        std::string GetSymbol() {
          if (op_ == kAdd) return "+";
          if (op_ == kSubtract) return "-";
          if (op_ == kMultiply) return "*";
          if (op_ == kDivide) return "/";
          if (op_ == kAssign) return "=";
        }
      private:
        Opcode op_;
      };

      class StatementNode { // this is our quadruple form of the ir
      public:               // the last field is the next statement pointer
        StatementNode(Operand* target,
          Operator* instruction,
          Operand* operand1,
          Operand* operand2,
          StatementNode* next)
          : target_(target),
          operator_(instruction),
          operand1_(operand1),
          operand2_(operand2),
          next_(next) {}
        ~StatementNode() {
          delete target_;
          delete operator_;
          delete operand1_;
          delete operand2_;
        }
        void Print() {
          if (target_ != nullptr) std::cout << target_->GetName();
          std::cout << " = ";
          if (operand1_ != nullptr) std::cout << GetOp1().GetName() << " ";
          if (operator_ != nullptr && operator_->GetOpcode() != Operator::kAssign) std::cout << GetInstruction().GetSymbol() << " ";
          if (operand2_ != nullptr) std::cout << GetOp2().GetName() << " ";
        }
        Operand& GetOp1() { return *operand1_; }
        Operand& GetOp2() { return *operand2_; }
        Operand& GetTarget() { return *target_; }
        Operator& GetInstruction() { return *operator_; }
        StatementNode*& GetNext() { return next_; }
      private:
        Operand * target_;
        Operator* operator_;
        Operand* operand1_;
        Operand* operand2_;
        StatementNode* next_;
      };
    } //namespace ir

  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_IR_V1_H_
