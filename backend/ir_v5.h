// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V5_H_
#define BACKEND_IR_V5_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "utility/memory.h"

using std::stringstream;
using std::endl;
using std::string;
using std::cout;

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
    class Operator {
    public:
      enum Opcode {
        kAdd, kSubtract, kMultiply, kDivide,
        kLessThan, kLessThanEqualTo, kGreaterThan, kGreaterThanEqualTo,
        kEqualTo, kGoto,
        kProgramStart, kProgramEnd,
        kFuncBegin, kFuncEnd, kReturn, kParam, kCall,
        kPushValueOfInteger, kPushAddressOfVariable, kPushValueOfVariable,
        kPushAddressOfDereference, kPushValueOfDereference, kAssignmentFromNewTuple,
        kAssignmentFromArithExp
      };
      explicit Operator(Opcode o) { op_ = (o); }
      ~Operator() {}
      Opcode GetOpcode() const { return op_; }
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
        delete GetOp2();
      }
      void Print() {
        cout << "#S" << label_->GetValue() << ":\t";
        switch (GetInstruction()->GetOpcode()) {
        case Operator::kAdd:
          cout << GetTarget()->GetName() << " = " << GetOp1()->GetName() << " + " << GetOp2()->GetName();
          break;
        case Operator::kSubtract:
          cout << GetTarget()->GetName() << " = " << GetOp1()->GetName() << " - " << GetOp2()->GetName();
          break;
        case Operator::kMultiply:
          cout << GetTarget()->GetName() << " = " << GetOp1()->GetName() << " * " << GetOp2()->GetName();
          break;
        case Operator::kDivide:
          cout << GetTarget()->GetName() << " = " << GetOp1()->GetName() << " / " << GetOp2()->GetName();
          break;
        case Operator::kAssignmentFromArithExp:
          cout << "*" << GetTarget()->GetName() << " = " << GetOp2()->GetName(); // a=5  a is target 2 is in op2, if theres is a single argument in the Three adress code, we normally put it in the second op field
          break;
        case Operator::kAssignmentFromNewTuple:
          cout << GetTarget()->GetName() << " = newTuple(" << GetOp2()->GetName() << ")";  
          break;
        case Operator::kLessThan:
          cout << "if (" << GetOp1()->GetName() << " < " << GetOp2()->GetName() << ") goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kLessThanEqualTo:
          cout << "if (" << GetOp1()->GetName() << " <= " << GetOp2()->GetName() << ") goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kGreaterThan:
          cout << "if (" << GetOp1()->GetName() << " > " << GetOp2()->GetName() << ") goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kGreaterThanEqualTo:
          cout << "if (" << GetOp1()->GetName() << " >= " << GetOp2()->GetName() << ") goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kEqualTo:
          cout << "if (" << GetOp1()->GetName() << " == " << GetOp2()->GetName() << ") goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kGoto:
          cout << "goto S" << GetTarget()->GetValue() << ":";
          break;
        case Operator::kProgramStart:
          cout << "program begin";
          break;
        case Operator::kProgramEnd:
          cout << "program end";
          break;
        case Operator::kCall:
          cout << "call " << GetTarget()->GetName() << "," << GetOp2()->GetValue() << "  --> " << operand1_->GetName(); //op2 is num of args
          break;
        case Operator::kParam:
          cout << "param " << GetTarget()->GetName();
          break;
        case Operator::kFuncBegin:
          cout << "func begin " << GetTarget()->GetName();
          break;
        case Operator::kFuncEnd:
          cout << "func end " << GetTarget()->GetName();
          break;
        case Operator::kReturn:
          cout << "return " << GetTarget()->GetName();
          break;
        case Operator::kPushValueOfInteger:
          cout << GetTarget()->GetName() << " = " << GetOp2()->GetName();
          break;
        case Operator::kPushValueOfVariable:
          cout << GetTarget()->GetName() << " = " << GetOp2()->GetName();
          break;
        case Operator::kPushAddressOfVariable:
          cout << GetTarget()->GetName() << " = &" << GetOp2()->GetName();
          break;
        case Operator::kPushAddressOfDereference:
          cout << GetTarget()->GetName() << " = &[" << GetOp1()->GetName() << "[" << GetOp2()->GetName() << "]]";
          break;
        case Operator::kPushValueOfDereference:
          cout << GetTarget()->GetName() << " = [" << GetOp1()->GetName() << "[" << GetOp2()->GetName() << "]]";
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

#endif  // BACKEND_IR_V5_H_
