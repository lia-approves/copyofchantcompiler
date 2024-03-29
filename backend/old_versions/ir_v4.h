// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V4_H_
#define BACKEND_IR_V4_H_

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

    class Operand {        // abstract class for operand can be constant(integer),
    public:               // variable or register or label
      Operand() {}
      virtual ~Operand() {}
      virtual int GetValue() = 0;
      virtual void SetValue(int value) = 0;
      virtual std::string GetName() = 0;
      virtual void SetStackOffset(int offset) = 0;
      virtual int GetStackOffset() = 0;
    private:
    };

    class Label : public Operand {
    public:
      explicit Label(int labelNum) { value_ = (labelNum); }
      ~Label() {}
      int GetValue() { return value_; }
      void SetValue(int value) { value_ = value; }
      std::string GetName() { return "statementnumber_" + std::to_string(value_); }
      void SetStackOffset(int offset) {  }
      int GetStackOffset() { return 0; }
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
      void SetStackOffset(int offset) { }
      int GetStackOffset() { return 0; }
    private:
      int value_;
    };

    class Variable : public Operand {     // bob, a, b, height, etc
    public:
      explicit Variable(std::string s) { name_ = (s); }
      ~Variable() {}
      int GetValue() { return 0; }
      std::string GetName() { return name_; }
      void SetValue(int value) {}
      void SetStackOffset(int offset) { stackOffSet_ = offset; }
      int GetStackOffset() { return stackOffSet_; }
    private:
      std::string name_;
      int stackOffSet_;
    };

    class Constant : public Operand {    // 3, 8, 6 etc (integers)
    public:
      explicit Constant(int v) { value_ = (v); }
      ~Constant() {}
      int GetValue() { return value_; }
      void SetValue(int value) { value_ = value; }
      std::string GetName() { return std::to_string(value_); }
      void SetStackOffset(int offset) {  }
      int GetStackOffset() { return 0; }
    private:
      int value_;
    };
    /*
    class Text : public Operand {                       // 3, 8, 6 etc (integers)
    public:
      explicit Text(string text) { text_ = (text); }
      ~Text() {}
      int GetValue() { return 0; }
      void SetValue(int value) { text_ = value; }
      std::string GetName() { return text_; }
      void SetStackOffset(int offset) {}
      int GetStackOffset() { return 0; }
    private:
      std::string text_;
    };*/

    class Operator {
    public:
      enum Opcode {
        kAdd, kSubtract, kMultiply, kDivide,
        kAssign, kLessThan, kLessThanEqualTo, kGreaterThan,
        kGreaterThanEqualTo, kEqualTo, kGoto, kAllocateVars,
        kDeallocateVars, kPrint, kRegister, kProgramStart, 
        kCall, kFuncBegin, kFuncEnd, kReturn,kParam
      };
      explicit Operator(Opcode o) { op_ = (o); }
      ~Operator() {}
      Opcode GetOpcode() const { return op_; }
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
        if (op_ == kGoto) return "-->";
        if (op_ == kAllocateVars) return "alloc";
        if (op_ == kDeallocateVars) return "dealloc";
        if (op_ == kPrint) return "print";
        if (op_ == kPrint) return "";
      }

    private:
      Opcode op_;
    };
    class StatementNode {
    public:
      StatementNode(
        Operand* label,
        Operand* target,
        Operator* instruction,
        Operand* operand1,
        Operand* operand2,
        StatementNode* next)
        : label_(label),
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
        std::cout << "#S";
        if (label_ != nullptr) std::cout << label_->GetValue() << ":\t";
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
          std::cout << "if (";
          if (operand1_ != nullptr) std::cout << GetOp1()->GetName() << " ";
          std::cout << GetInstruction()->GetSymbol() << " ";
          if (operand2_ != nullptr) std::cout << GetOp2()->GetName() << "";
          std::cout << ") goto S";
          if (target_ != nullptr) std::cout << target_->GetValue() << ":";
          break;

        case Operator::kGoto:
          if (target_ != nullptr) {
            std::cout << "goto S" << target_->GetValue() << ":";
          }
          break;
        case Operator::kAllocateVars:
          if (target_ != nullptr) {
            std::cout << "alloc " << target_->GetValue() << " loc vars:";
          }
          break;
        case Operator::kDeallocateVars:
          if (target_ != nullptr) {
            std::cout << "dealloc " << 8 << "*" << target_->GetValue() << " bytes:";
          }
          break;
        case Operator::kPrint:
          if (target_ != nullptr) {
            std::cout << "" << target_->GetName() << "";
          }
          break;
        case Operator::kRegister:
          if (Constant* regType = dynamic_cast<Constant*>(operand2_)) {
            std::cout << "" << target_->GetName() << " = " << regType->GetName();
          }
          else if (Variable* regType = dynamic_cast<Variable*>(operand2_)) {
            std::cout << target_->GetName() << " = " << regType->GetName();
          }
          else if (Register* regType = dynamic_cast<Register*>(operand2_)) {
            std::cout << regType->GetName() << " = " << target_->GetName();
          }
          break;
        case Operator::kProgramStart:
          std::cout << "program begin";
          break;
        case Operator::kCall:
          std::cout << "call " << target_->GetName() << "," << operand2_->GetValue() << "  --> " << operand1_->GetName();
          break;
        case Operator::kParam:
          std::cout << "param " << target_->GetName();
          break;
        case Operator::kFuncBegin:
          std::cout << "func begin " << target_->GetName();
          break;
        case Operator::kFuncEnd:
          std::cout << "func end " << target_->GetName();
          break;
        case Operator::kReturn:
          std::cout << "return " << target_->GetName();
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
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_IR_V4_H_
