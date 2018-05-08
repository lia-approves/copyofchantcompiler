// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V3_H_
#define BACKEND_IR_V3_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"

using std::stringstream;
using std::endl;
using std::string;

namespace cs160 {
  namespace backend {
    namespace ir {

      class Operand {                                          //abstract class for operand can be constant(integer), 
      public:                                                  //variable or register or label
        Operand() {}
        virtual ~Operand() {}
        virtual int GetValue() = 0;
        virtual void SetValue(int value) = 0;
        virtual std::string GetName() = 0;
        virtual void PushToAsmSS(stringstream& ss) = 0;
        virtual void PopToAsmSS(stringstream& ss, string register_) = 0;
      private:
      };

      class Label : public Operand {
      public:
        Label(int labelNum) { value_ = (labelNum); }
        ~Label() {}
        int GetValue() { return value_; }
        void SetValue(int value) { value_ = value; }
        std::string GetName() { return "statementnumber_" + std::to_string(value_); }
        void PushToAsmSS(stringstream& ss) {}
        void PopToAsmSS(stringstream& ss, string register_) {}
      private:
        int value_;
      };

      class Register : public Operand {                        // t1, t2 ,etc
      public:
        explicit Register(int v) { value_ = (v); }
        ~Register() {}
        int GetValue() { return value_; }
        void SetValue(int value) { value_ = value; }
        std::string GetName() { return "t" + std::to_string(value_); }
        void PushToAsmSS(stringstream& ss) { /* There is nothing to push because it's a register*/ }
        void PopToAsmSS(stringstream& ss, string register_) { ss << "pop " << register_ << endl; }
      private:
        int value_;
      };

      class Variable : public Operand {                        // bob, a, b, height, etc
      public:
        explicit Variable(std::string s) { name_ = (s); }
        ~Variable() {}
        int GetValue() {}                          
        std::string GetName() { return name_; }
        void SetValue(int value) {}
        void PushToAsmSS(stringstream& ss) { ss << "push (" << name_ << ")" << endl; }
        void PopToAsmSS(stringstream& ss, string register_) { ss << "pop (" << GetName() << ")" << endl; }
      private:
        std::string name_;
      };

      class Constant : public Operand {                       // 3, 8, 6 etc (integers)
      public:
        explicit Constant(int v) { value_ = (v); }
        ~Constant() {}
        int GetValue() { return value_; }
        void SetValue(int value) { value_ = value; }
        std::string GetName() { return std::to_string(value_); }
        void PushToAsmSS(stringstream& ss) { ss << "push $" << value_ << endl; }
        void PopToAsmSS(stringstream& ss, string register_) { ss << "pop " << register_ << endl; }
      private:
        int value_;
      };

      class Operator {    
      public:
        enum Opcode {
          kAdd, kSubtract, kMultiply, kDivide, kAssign, kLessThan, kLessThanEqualTo,
          kGreaterThan, kGreaterThanEqualTo, kEqualTo, kLogicalAnd, kLogicalOr, kLogicalNot, kGoto
        };
        explicit Operator(Opcode o) { op_ = (o); }
        ~Operator() {}
        Opcode GetOpcode() const { return op_; }
        std::string GetName() {
          if (op_ == kAdd) return "add";
          if (op_ == kSubtract) return "subtract";
          if (op_ == kMultiply) return "multiply";
          if (op_ == kDivide) return "divide";
          if (op_ == kAssign) return "assign";
          if (op_ == kLessThan) return "less than";
          if (op_ == kLessThanEqualTo) return "less than or equal to";
          if (op_ == kGreaterThan) return "greater than";
          if (op_ == kGreaterThanEqualTo) return "greater than or equal to";
          if (op_ == kEqualTo) return "equal to";
          if (op_ == kLogicalAnd) return "and";
          if (op_ == kLogicalOr) return "or";
          if (op_ == kLogicalNot) return "not";
          if (op_ == kGoto) return "goto";
        }
        std::string GetSymbol() {
          if (op_ == kAdd) return "+";
          if (op_ == kSubtract) return "-";
          if (op_ == kMultiply) return "*";
          if (op_ == kDivide) return "/";
          if (op_ == kAssign) return "=";
          if (op_ == kLessThan) return "<";
          if (op_ == kLessThanEqualTo) return "<=";
          if (op_ == kGreaterThan) return ">";
          if (op_ == kGreaterThanEqualTo) return ">=";
          if (op_ == kEqualTo) return "==";
          if (op_ == kLogicalAnd) return "&&";
          if (op_ == kLogicalOr) return "||";
          if (op_ == kLogicalNot) return "!";
          if (op_ == kGoto) return "-->";
        }
      private:
        Opcode op_;
      };
      class StatementNode {                                   
      public:                                                 // the last field is the next statement pointer
        StatementNode(
          Operand* label,
          Operand* target,
          Operator* instruction,
          Operand* operand1,
          Operand* operand2,
          StatementNode* next)
          :
          label_(label),
          target_(target),
          operator_(instruction),
          operand1_(operand1),
          operand2_(operand2),
          next_(next) {}
        ~StatementNode() {
          delete label_;
          delete target_;
          delete operator_;
          delete operand1_;
          delete operand2_;
        }
        void Print() {
          std::cout << "# S" << label_->GetValue() << ":  ";
          switch (GetInstruction()->GetOpcode()) {
          case Operator::kAdd:
          case Operator::kSubtract:
          case Operator::kMultiply:
          case Operator::kDivide:
            if (target_ != nullptr) std::cout << target_->GetName();
            std::cout << " = ";
            if (operand1_ != nullptr) std::cout << GetOp1()->GetName() << " ";
            std::cout << GetInstruction()->GetSymbol() << " ";
            if (operand2_ != nullptr) std::cout << GetOp2()->GetName();
            break;

          case Operator::kAssign:
            if (target_ != nullptr) std::cout << target_->GetName();
            std::cout << " = ";
            if (operand2_ != nullptr) std::cout << GetOp2()->GetName();
            break;

          case Operator::kLessThan:
          case Operator::kLessThanEqualTo:
          case Operator::kGreaterThan:
          case Operator::kGreaterThanEqualTo:
          case Operator::kEqualTo:
          case Operator::kLogicalAnd:
          case Operator::kLogicalOr:
            std::cout << "if (";
            if (operand1_ != nullptr) std::cout << GetOp1()->GetName() << " ";
            std::cout << GetInstruction()->GetSymbol() << " ";
            if (operand2_ != nullptr) std::cout << GetOp2()->GetName() << "";
            std::cout << ") goto S";
            if (target_ != nullptr) std::cout << target_->GetValue() << ":";
            break;

          case Operator::kGoto:
            if (target_ != nullptr) std::cout << "goto S" << target_->GetValue() << ":";
            break;

          case Operator::kLogicalNot: //unused
            break;

          default:
            break;
          }
        }
        Operand*& GetLabel() { return label_; }
        Operand*& GetOp1() { return operand1_; }
        Operand*& GetOp2() { return operand2_; }
        Operand*& GetTarget() { return target_; }
        Operator*& GetInstruction() { return operator_; }
        StatementNode*& GetNext() { return next_; }
      private:
        Operand * label_;
        Operand * target_;
        Operator* operator_;
        Operand* operand1_;
        Operand* operand2_;
        StatementNode* next_;
      };
    } //namespace ir
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_IR_V3_H_
