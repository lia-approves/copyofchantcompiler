// Copyright(c) 2018, Team Chant

#ifndef BACKEND_IR_V5_H_
#define BACKEND_IR_V5_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
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
      virtual void SetName(string name) = 0;
      virtual std::string GetName() = 0;
    private:
    };

    class Register : public Operand {                        // t1, t2 ,etc
    public:
      explicit Register(int v) { value_ = (v); }
      ~Register() {}
      int GetValue() { return value_; }
      void SetValue(int value) { value_ = value; }
      std::string GetName() { return "t" + std::to_string(value_); }
      void SetName(std::string name) {  }
    private:
      int value_;
    };

    class Variable : public Operand {     // bob, a, b, height, etc
    public:
      explicit Variable(std::string s) { name_ = (s); }
      ~Variable() {}
      int GetValue() { return 0; }
      std::string GetName() { return name_+subscript_; }
      void SetSubscript(string subscript) { subscript_= subscript; }
      std::string GetSubscript() { return subscript_; }
      std::string GetNameWithoutSubscript() { return name_; }
      void SetValue(int value) {}
      void SetName(std::string name) { name_ = name; }

    private:
      std::string name_;
      string subscript_ = "";

    };

    class Constant : public Operand {    // 3, 8, 6 etc (integers)
    public:
      explicit Constant(int v) { value_ = (v); }
      ~Constant() {}
      int GetValue() { return value_; }
      void SetValue(int value) { value_ = value; }
      std::string GetName() { return std::to_string(value_); }
      void SetName(std::string name) {  }

    private:
      int value_;
    };
    class Label {
    public:
      explicit Label(int labelNum) { value_ = labelNum; }
      ~Label() {}
      int GetValue() { return value_; }
      void SetValue(int newValue) { value_= newValue; }
      void SetName(std::string name) { }

    private:
      int value_;
    };

    class Instruction {
    public:
      enum Opcode {
        kAdd, kSubtract, kMultiply, kDivide,
        kLessThan, kLessThanEqualTo, kGreaterThan, kGreaterThanEqualTo,
        kEqualTo, kGoto,
        kProgramStart, kProgramEnd,
        kFuncBegin, kParam, kFuncEnd, kReturn, kArgument, kCall,
        kValueOfInteger, kAddressOfVariable, kValueOfVariable,
        kAddressOfDereference, kValueOfDereference, kAssignmentFromNewTuple,
        kAssignmentFromArithExp, kAssignmentToVariable, kPhiFunction
      };
      explicit Instruction(Opcode o) { op_ = (o); }
      ~Instruction() {}
      Opcode GetOpcode() const { return op_; }
    private:
      Opcode op_;
    };
    class StatementNode {
    public:
      StatementNode(
        std::unique_ptr<Label> label,
        std::unique_ptr<Operand> target,
        std::unique_ptr<Instruction> instruction,
        std::unique_ptr<Operand> operand1,
        std::unique_ptr<Operand> operand2)
        : label_(std::move(label)),
        target_(std::move(target)),
        instruction_(std::move(instruction)),
        operand1_(std::move(operand1)),
        operand2_(std::move(operand2)) {}
      ~StatementNode() {}
      void Print() {
        cout << "#   S" << GetLabel().GetValue() << ":  ";
        switch (GetInstruction().GetOpcode()) {
        case Instruction::kAdd:
          cout << GetTarget().GetName() << " = " << GetOp1().GetName() << " + " << GetOp2().GetName();
          break;
        case Instruction::kSubtract:
          cout << GetTarget().GetName() << " = " << GetOp1().GetName() << " - " << GetOp2().GetName();
          break;
        case Instruction::kMultiply:
          cout << GetTarget().GetName() << " = " << GetOp1().GetName() << " * " << GetOp2().GetName();
          break;
        case Instruction::kDivide:
          cout << GetTarget().GetName() << " = " << GetOp1().GetName() << " / " << GetOp2().GetName();
          break;
        case Instruction::kLessThan:
          cout << "if (" << GetOp1().GetName() << " < " << GetOp2().GetName() << ") goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kLessThanEqualTo:
          cout << "if (" << GetOp1().GetName() << " <= " << GetOp2().GetName() << ") goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kGreaterThan:
          cout << "if (" << GetOp1().GetName() << " > " << GetOp2().GetName() << ") goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kGreaterThanEqualTo:
          cout << "if (" << GetOp1().GetName() << " >= " << GetOp2().GetName() << ") goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kEqualTo:
          cout << "if (" << GetOp1().GetName() << " == " << GetOp2().GetName() << ") goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kGoto:
          cout << "goto S" << GetTarget().GetValue() << ":";
          break;
        case Instruction::kProgramStart:
          cout << "main program begin";
          break;
        case Instruction::kParam:
          cout << "param " << GetTarget().GetName();
          break;
        case Instruction::kProgramEnd:
          cout << "main program end";
          break;
        case Instruction::kCall:
          cout << "call " << GetTarget().GetName() << "," << GetOp2().GetValue() << "  --> " << GetOp1().GetName(); //op2 is num of args
          break;
        case Instruction::kArgument:
          cout << "argument " << GetTarget().GetName();
          break;
        case Instruction::kFuncBegin:
          cout << "func begin " << GetTarget().GetName();
          break;
        case Instruction::kFuncEnd:
          cout << "func end " << GetTarget().GetName();
          break;
        case Instruction::kReturn:
          cout << "return " << GetTarget().GetName();
          break;
        case Instruction::kValueOfInteger:
          cout << GetTarget().GetName() << " = " << GetOp2().GetName();
          break;
        case Instruction::kValueOfVariable:
          cout << GetTarget().GetName() << " = " << GetOp2().GetName();
          break;
        case Instruction::kAddressOfVariable:
          cout << GetTarget().GetName() << " = &" << GetOp2().GetName();
          break;
        case Instruction::kAddressOfDereference:
          cout << GetTarget().GetName() << " = &" << GetOp1().GetName() << "[" << GetOp2().GetName() << "]";
          break;
        case Instruction::kValueOfDereference:
          cout << GetTarget().GetName() << " = " << GetOp1().GetName() << "[" << GetOp2().GetName() << "]";
          break;
        case Instruction::kAssignmentFromArithExp:
          cout << "*" << GetTarget().GetName() << " = " << GetOp2().GetName(); // a=5  a is target 2 is in op2, if theres is a single argument in the Three adress code, we normally put it in the second op field
          break;
        case Instruction::kAssignmentToVariable:
          cout << GetTarget().GetName() << " = " << GetOp2().GetName(); // a=5  a is target 2 is in op2, if theres is a single argument in the Three adress code, we normally put it in the second op field
          break;
        case Instruction::kAssignmentFromNewTuple:
          cout << "*" << GetTarget().GetName() << " = newTuple(" << GetOp2().GetName() << ")";
          break;
        case Instruction::kPhiFunction:
          cout << GetTarget().GetName() << " = phi(" << GetOp2().GetName()<<")";
          break;
        }
      }
      Label& GetLabel() { return *label_; }
      Operand& GetOp1() { return *operand1_; }
      Operand& GetOp2() { return *operand2_; }
      Operand& GetTarget() { return *target_; }
      Instruction& GetInstruction() { return *instruction_; }
    private:
      std::unique_ptr<Label> label_;
      std::unique_ptr<Operand> target_;
      std::unique_ptr<Instruction> instruction_;
      std::unique_ptr<Operand> operand1_;
      std::unique_ptr<Operand> operand2_;
    };
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_IR_V5_H_
