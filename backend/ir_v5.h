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

namespace cs160 {
namespace backend {

class Operand {        // abstract class for operand can be constant(integer),
 public:               // variable or register or label
  Operand() {}
  virtual ~Operand() {}

  virtual std::string GetName() = 0;

  virtual void SetBase(Operand *base) = 0;
  virtual Operand* GetBase() = 0;

  virtual void SetOffset(Operand *offset) = 0;
  virtual Operand* GetOffset() = 0;

  virtual std::string PushValueToStack() = 0;
  virtual std::string PushAddrToStack() = 0;

 private:
  std::string name_;
  Operand *offset_;
  Operand *base_;
};

class Label : public Operand {
 public:
  explicit Label(int labelNum) { value_ = (labelNum); }
  ~Label() {}
  int GetValue() { return value_; }
  void SetValue(int value) { value_ = value; }
  std::string GetName() { return "statementnumber_" + std::to_string(value_); }
  void SetOffset(Operand *offset) {  }
  void SetBase(Operand *base) {  }
  Operand* GetOffset() { return offset_; }
  Operand* GetBase() { return base_; }
  std::string PushValueToStack() {
    return "";
  }
  std::string PushAddrToStack() {
    return "";
  }
 private:
  int value_;
  Operand *base_;
  Operand *offset_;
};

class Register : public Operand {                        // t1, t2 ,etc
 public:
  explicit Register(int v) { value_ = (v); }
  ~Register() {}
  int GetValue() { return value_; }
  void SetValue(int value) { value_ = value; }
  std::string GetName() { return "t" + std::to_string(value_); }
  void SetOffset(Operand *offset) {  }
  void SetBase(Operand *base) {  }

  Operand* GetOffset() { return offset_; }

  Operand* GetBase() { return base_; }

  std::string PushValueToStack() {
    return "";
  }
  std::string PushAddrToStack() {
    return "";
  }
 private:
  int value_;
  Operand *base_;
  Operand *offset_;
};

class Variable : public Operand {
  // A Variable refers to a value stored in memory, either the heap or the stack
  // It is defined by a base pointer... eg:
  // for a tuple "-8(%rbp)", for a var "%rbp"
  // and an offset, which is the location of the value relative to either the
  // stack (in the case of a local variable) or a tuple address (in the case of
  // a dereference of a tuple)
 public:
  explicit Variable(std::string s) {
    name_ = s;
    // base_ = new Constant("%rbp");
    // offset_ = new Constant("$0");
  }
  ~Variable() {}

  std::string GetName() { return name_; }

  void SetOffset(Operand *offset) {
    offset_ = offset;
  }
  Operand* GetOffset() { return offset_; }

  void SetBase(Operand *base) {
    base_ = base;
  }
  Operand* GetBase() { return base_; }

  std::string PushValueToStack() {
    std::stringstream res;
    res << base_->PushAddrToStack();
    res << offset_->PushValueToStack();
    res << "pop %rax" << endl;  // rax contains the offset
    res << "pop %rbx" << endl;  // rbx contains the base addr
    res << "add %rax, %rbx" << endl;
    res << "push (%rbx)" << endl;
    return res.str();
  }
  std::string PushAddrToStack() {
    std::stringstream res;
    res << base_->PushAddrToStack();
    res << offset_->PushValueToStack();
    res << "pop %rax" << endl;  // rax contains the offset
    res << "pop %rbx" << endl;  // rbx contains the base addr
    res << "add %rax, %rbx" << endl;
    res << "push %rbx" << endl;
    return res.str();
  }

 private:
  std::string name_;
  Operand *offset_;
  Operand *base_;
};

class Deref : public Operand {
 public:
  explicit Deref(std::string s) {
    name_ = s;
  }
  ~Deref() {}

  std::string GetName() { return name_; }
  void SetOffset(Operand *offset) {
    offset_ = offset;
  }
  void SetBase(Operand *base) {
    base_ = base;
  }
  Operand* GetOffset() { return offset_; }
  Operand* GetBase() { return base_; }

  std::string PushValueToStack() {
    std::stringstream res;
    res << base_->PushValueToStack();
    // res << base_->PushAddrToStack();
    res << offset_->PushValueToStack();
    res << "pop %rax" << endl;  // rax contains the offset
    res << "imul $8, %rax" << endl;
    res << "pop %rbx" << endl;  // rbx contains the base addr
    res << "add %rax, %rbx" << endl;
    res << "push (%rbx)" << endl;
    return res.str();
  }
  std::string PushAddrToStack() {
    std::stringstream res;
    res << base_->PushValueToStack();
    // res << base_->PushAddrToStack();
    res << offset_->PushValueToStack();
    res << "pop %rax" << endl;  // rax contains the offset
    res << "imul $8, %rax" << endl;
    res << "pop %rbx" << endl;  // rbx contains the base addr
    res << "add %rax, %rbx" << endl;
    res << "push %rbx" << endl;
    return res.str();
  }

 private:
  std::string name_;
  Operand *offset_;
  Operand *base_;
};

class Constant : public Operand {    // 3, 8, 6 etc (integers)
 public:
  explicit Constant(std::string n) { name_ = (n); }
  ~Constant() {}

  std::string GetName() { return name_; }

  void SetOffset(Operand *offset) {  }
  Operand* GetOffset() { return offset_; }

  Operand* GetBase() { return base_; }
  void SetBase(Operand *base) {  }

  std::string PushValueToStack() {
    std::stringstream res;
    res << "push $" << name_ << endl;
    return res.str();
  }
  std::string PushAddrToStack() {
    std::stringstream res;
    res << "push " << name_ << endl;
    return res.str();
  }

 private:
  std::string name_;
  Operand *offset_;
  Operand *base_;
};


class Operator {
 public:
  enum Opcode {
    kAdd, kSubtract, kMultiply, kDivide,
    kAssignFromArithExp, kAssignFromNewTuple, kLessThan, kLessThanEqualTo,
    kGreaterThan, kGreaterThanEqualTo, kEqualTo, kGoto, kAllocateVars,
    kDeallocateVars, kPrint, kPushVarValue, kProgramStart,
    kCall, kFuncBegin, kFuncEnd, kReturn, kParam, kPushAddr
  };
  explicit Operator(Opcode o) { op_ = (o); }
  ~Operator() {}
  Opcode GetOpcode() const { return op_; }
  std::string GetSymbol() {
    if (op_ == kAdd) return "+";
    if (op_ == kSubtract) return "-";
    if (op_ == kMultiply) return "*";
    if (op_ == kDivide) return "/";
    if (op_ == kAssignFromArithExp) return "=";
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
    return "";
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
    if (label_ != nullptr) std::cout << label_->GetName() << ":\t";
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

    case Operator::kAssignFromArithExp:
      if (target_ != nullptr) std::cout << target_->GetName();
      std::cout << " = ";
      if (operand2_ != nullptr) std::cout << GetOp2()->GetName();
      break;
    case Operator::kAssignFromNewTuple:
      if (target_ != nullptr) std::cout << target_->GetName();
      std::cout << " := ";
      if (operand2_ != nullptr) std::cout << "(" << GetOp2()->GetName() << ")";
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
      if (target_ != nullptr) std::cout << target_->GetName() << ":";
      break;

    case Operator::kGoto:
      if (target_ != nullptr) {
        std::cout << "goto S" << target_->GetName() << ":";
      }
      break;
    case Operator::kAllocateVars:
      if (target_ != nullptr) {
        std::cout << "alloc " << target_->GetName() << " loc vars:";
      }
      break;
    case Operator::kDeallocateVars:
      if (target_ != nullptr) {
        std::cout << "dealloc " << 8 << "*" << target_->GetName() << " bytes:";
      }
      break;
    case Operator::kPrint:
      if (target_ != nullptr) {
        std::cout << "" << target_->GetName() << "";
      }
      break;
    case Operator::kPushVarValue:
      if (Constant* regType = dynamic_cast<Constant*>(operand2_)) {
        std::cout << "" << target_->GetName() << " = " << regType->GetName();
      } else if (Variable* regType = dynamic_cast<Variable*>(operand2_)) {
        std::cout << target_->GetName() << " = " << regType->GetName();
      } else if (Register* regType = dynamic_cast<Register*>(operand2_)) {
        std::cout << regType->GetName() << " = " << target_->GetName();
      }
      break;
    case Operator::kProgramStart:
      std::cout << "program begin";
      break;
    case Operator::kCall:
      std::cout << "call " << target_->GetName() << ","
      << operand2_->GetName() << "  --> " << operand1_->GetName();
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

#endif  // BACKEND_IR_V5_H_
