// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V4_H_
#define BACKEND_LOWERER_V4_H_

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v4.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v4.h"


using cs160::abstract_syntax::version_4::IntegerExpr;
using cs160::abstract_syntax::version_4::ArithmeticBinaryOperatorExpr;
using cs160::abstract_syntax::version_4::AddExpr;
using cs160::abstract_syntax::version_4::SubtractExpr;
using cs160::abstract_syntax::version_4::MultiplyExpr;
using cs160::abstract_syntax::version_4::DivideExpr;
using cs160::abstract_syntax::version_4::AstNode;
using cs160::abstract_syntax::version_4::AstVisitor;
using cs160::abstract_syntax::version_4::VariableExpr;
using cs160::abstract_syntax::version_4::Assignment;
using cs160::abstract_syntax::version_4::Program;
using cs160::abstract_syntax::version_4::LessThanExpr;
using cs160::abstract_syntax::version_4::LessThanEqualToExpr;
using cs160::abstract_syntax::version_4::GreaterThanExpr;
using cs160::abstract_syntax::version_4::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_4::EqualToExpr;
using cs160::abstract_syntax::version_4::LogicalAndExpr;
using cs160::abstract_syntax::version_4::LogicalOrExpr;
using cs160::abstract_syntax::version_4::LogicalNotExpr;
using cs160::abstract_syntax::version_4::Conditional;
using cs160::abstract_syntax::version_4::Loop;
using cs160::abstract_syntax::version_4::FunctionCall;
using cs160::abstract_syntax::version_4::FunctionDef;


using cs160::backend::StatementNode;
using cs160::backend::Constant;
using cs160::backend::Label;
using cs160::backend::Operator;
using cs160::backend::Register;
using cs160::backend::Operand;
using cs160::backend::Variable;
using std::cout;


namespace cs160 {
namespace backend {
class CountVisitor : public AstVisitor {
 public:
  void VisitIntegerExpr(const IntegerExpr& exp) override;

  void VisitVariableExpr(const VariableExpr& exp) override;

  void VisitAddExpr(const AddExpr& exp) override;

  void VisitSubtractExpr(const SubtractExpr& exp) override;

  void VisitMultiplyExpr(const MultiplyExpr& exp) override;

  void VisitDivideExpr(const DivideExpr& exp) override;

  void VisitLessThanExpr(const LessThanExpr& exp) override;

  void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) override;

  void VisitGreaterThanExpr(const GreaterThanExpr& exp) override;

  void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) override;
  void VisitEqualToExpr(const EqualToExpr& exp) override;

  void VisitLogicalAndExpr(const LogicalAndExpr& exp) override;

  void VisitLogicalOrExpr(const LogicalOrExpr& exp) override;

  void VisitLogicalNotExpr(const LogicalNotExpr& exp) override;

  void VisitAssignment(const Assignment& assignment) override;

  void VisitConditional(const Conditional& conditional) override;

  void VisitLoop(const Loop& loop) override;

  void VisitProgram(const Program& program) override;
  void VisitFunctionCall(const FunctionCall& call) override;

  void VisitFunctionDef(const FunctionDef& def) override;

  void ScanningParams(bool scanningParams);
  int LocalVars() { return localVariables_.size(); }
  int ParamVars() { return paramVariables_.size(); }

 private:
  bool scanningParams_ = false;
  std::vector<string> paramVariables_;
  std::vector<string> localVariables_;
};
class IrGenVisitor : public AstVisitor {
 public:
  IrGenVisitor() {}
  ~IrGenVisitor() {
    StatementNode* tobe_deleted = head_;
    while (tobe_deleted != nullptr) {
      delete tobe_deleted;
      tobe_deleted = tobe_deleted->GetNext();
    }
  }

  void VisitAddExpr(const AddExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Register(register_number_),
      new Operator(Operator::kAdd),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  void VisitSubtractExpr(const SubtractExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Register(register_number_),
      new Operator(Operator::kSubtract),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  void VisitMultiplyExpr(const MultiplyExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Register(register_number_),
      new Operator(Operator::kMultiply),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }

  void VisitDivideExpr(const DivideExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Register(register_number_),
      new Operator(Operator::kDivide),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
    stack_.pop_back();
    stack_.push_back(new Register(register_number_));
    register_number_++;
  }
  void VisitIntegerExpr(const IntegerExpr& exp) {
    stack_.push_back(new Constant(exp.value()));
    string main = "push $";
    main.append(std::to_string(exp.value()));
    main.append("\n");
    StatementNode* newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
  }
  void VisitVariableExpr(const VariableExpr& exp) {
    stack_.push_back(new Variable(exp.name()));
    int pos;
    int stackOffset;
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(),
      (exp.name())) != paramVariables_.end();
    if (foundinParams) {
      pos = std::distance(paramVariables_.begin(), std::find(
        paramVariables_.begin(), paramVariables_.end(), exp.name()));
      stackOffset = 1 * ((pos + 2) * 8);
      stack_.back()->SetStackOffset(stackOffset);
    } else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (exp.name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(exp.name()); }
        pos = std::distance(localVariables_.begin(), std::find(
          localVariables_.begin(),
          localVariables_.end(),
          exp.name()));
        stackOffset = -1 * ((pos + 1) * 8);
        stack_.back()->SetStackOffset(stackOffset);
      } else if (scanningParams_ == true) {
       if (!foundinParams) { paramVariables_.push_back(exp.name()); }
       pos = std::distance(paramVariables_.begin(), std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          exp.name()));
        stackOffset = 1 * ((pos + 2) * 8);
        stack_.back()->SetStackOffset(stackOffset);
      }
    }
    if (!scanningParams_) {
      string main = "push ";
      main.append(std::to_string(stackOffset));
      main.append("(%rbp)\n");
      StatementNode* newhead = new StatementNode(
        new Label(labelNum_++),
        new Text(main),
        new Operator(Operator::kPrint),
        nullptr,
        nullptr,
        nullptr);
      AddToEnd(newhead);
    }
  }
  void VisitAssignment(const Assignment& assignment) {
    int pos;
    int stackOffset;
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(),
      (assignment.lhs().name())) != paramVariables_.end();
    if (foundinParams) {
      pos = std::distance(paramVariables_.begin(), std::find(
        paramVariables_.begin(),
        paramVariables_.end(),
        assignment.lhs().name()));
      stackOffset = 1 * ((pos + 2) * 8);
    } else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (assignment.lhs().name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(assignment.lhs().name()); }
        pos = std::distance(localVariables_.begin(), std::find(
          localVariables_.begin(),
          localVariables_.end(),
          assignment.lhs().name()));
        stackOffset = -1 * ((pos + 1) * 8);
      } else if (scanningParams_ == true) {
        bool found = std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          (assignment.lhs().name())) != paramVariables_.end();
        if (!found) {
          paramVariables_.push_back(assignment.lhs().name());
        }
        pos = std::distance(paramVariables_.begin(), std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          assignment.lhs().name()));
        stackOffset = 1 * ((pos + 2) * 8);
      }
    }

    assignment.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Variable(assignment.lhs().name()),
      new Operator(Operator::kAssign),
      nullptr,
      op2,
      nullptr);
    newtail->GetTarget()->SetStackOffset(stackOffset);
    AddToEnd(newtail);
    stack_.push_back(new Register(register_number_));
  }
  void VisitProgram(const Program& program) {
    for (auto& def : program.function_defs()) {
      def->Visit(this);
    }
    CountVisitor varCount;
    varCount.ScanningParams(false);
    for (auto& statement : program.statements()) {
      statement->Visit(&varCount);
    }
    mainVars_ = varCount.LocalVars();
    string main = ".global main\n.text\nmain:\nmov %rsp, %rbp";
    StatementNode* newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    newhead = new StatementNode(
      new Label(labelNum_++),
      new Constant(varCount.LocalVars()),
      new Operator(Operator::kAllocateVars),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    for (auto& statement : program.statements()) { statement->Visit(this); }
    program.arithmetic_exp().Visit(this);
    localVariables_.clear();
  }
  void VisitFunctionCall(const FunctionCall& call) override {
    int numArgs = call.arguments().size();

    for (auto& arg : call.arguments()) {
      arg->Visit(this);
    }
    string main = "";
    main.append("call ");
    main.append(call.callee_name());
    main.append("\n");

    StatementNode* newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    int pos;
    int stackOffset;
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(),
      (call.lhs().name())) != paramVariables_.end();
    if (foundinParams) {
      pos = std::distance(paramVariables_.begin(), std::find(
        paramVariables_.begin(),
        paramVariables_.end(),
        call.lhs().name()));
      stackOffset = 1 * ((pos + 2) * 8);
    } else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (call.lhs().name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(call.lhs().name()); }
        pos = std::distance(localVariables_.begin(), std::find(
          localVariables_.begin(),
          localVariables_.end(),
          call.lhs().name()));
        stackOffset = -1 * ((pos + 1) * 8);
      } else if (scanningParams_ == true) {
        bool found = std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          (call.lhs().name())) != paramVariables_.end();
        if (!found) {
          paramVariables_.push_back(call.lhs().name());
        } else {}
        pos = std::distance(paramVariables_.begin(), std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          call.lhs().name()));
        stackOffset = 1 * ((pos + 2) * 8);
      }
    }
    main = "";
    main.append("push ");
    main.append("%rax\n");
    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);

    main = "";
    main.append("pop ");
    main.append(std::to_string(stackOffset));
    main.append("(%rbp)\n");
    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);

    main = "";
    main.append("add $");
    main.append(std::to_string(8 * numArgs));
    main.append(", %rsp\n");

    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
  }

  void VisitFunctionDef(const FunctionDef& def) override {
    StatementNode*newhead = new StatementNode(
      new Label(labelNum_++),
      new Text("###BEGIN FUNct DEF###"),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    CountVisitor varsCounter;
    varsCounter.ScanningParams(true);
    for (auto& param : def.parameters()) {
      param->Visit(&varsCounter);
    }
    varsCounter.ScanningParams(false);
    for (auto& statement : def.function_body()) {
      statement->Visit(&varsCounter);
    }
    int numLocalVar = varsCounter.LocalVars();
    string main = "";
    main.append(".type ");
    main.append(def.function_name());
    main.append(", @function\n");
    main.append(def.function_name());
    main.append(":\n");
    main.append("push %rbp\n");
    main.append("mov %rsp, %rbp\n");
    main.append("sub $");
    main.append(std::to_string(8 * numLocalVar));
    main.append(", %rsp\n");
    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    // we allocated local vars and know how many parameres and
    // local vars there are

    scanningParams_ = true;
    for (auto& param : def.parameters()) {
      param->Visit(this);
    }
    scanningParams_ = false;
    for (auto& statement : def.function_body()) {
      statement->Visit(this);
    }
    def.retval().Visit(this);
    main = "";
    main.append("pop %rax\n");

    main.append("mov %rbp, %rsp\n");
    main.append("pop %rbp\n");
    main.append("ret");
    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text(main),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);

    newhead = new StatementNode(
      new Label(labelNum_++),
      new Text("###END FUN DEF###"),
      new Operator(Operator::kPrint),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newhead);
    localVariables_.clear();
    paramVariables_.clear();
  }

  void VisitLessThanExpr(const LessThanExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kLessThan),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kLessThanEqualTo),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitGreaterThanExpr(const GreaterThanExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kGreaterThan),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kGreaterThanEqualTo),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitEqualToExpr(const EqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
    Operand* op2 = stack_.back();
    stack_.pop_back();
    Operand* op1 = stack_.back();
    stack_.pop_back();
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kEqualTo),
      op1,
      op2,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitLogicalAndExpr(const LogicalAndExpr& exp) {
    IrGenVisitor countVisitor;
    exp.rhs().Visit(&countVisitor);
    int numRhs = countVisitor.NumberOfStatements();
    exp.lhs().Visit(this);
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + numRhs),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
    exp.rhs().Visit(this);
  }
  void VisitLogicalOrExpr(const LogicalOrExpr& exp) {
    IrGenVisitor countVisitor;
    exp.rhs().Visit(&countVisitor);
    int numRhs = countVisitor.NumberOfStatements();
    exp.lhs().Visit(this);
    tail_->GetTarget()->SetValue(tail_->GetTarget()->GetValue() + numRhs);
    exp.rhs().Visit(this);
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
    newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitLogicalNotExpr(const LogicalNotExpr& exp) {
    exp.operand().Visit(this);
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(labelNum_ + 1),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
  }
  void VisitConditional(const Conditional& conditional) {
    IrGenVisitor trueVisitor;
    IrGenVisitor falseVisitor;
    for (auto& statement : conditional.true_branch()) {
      statement->Visit(&trueVisitor);
    }
    for (auto& statement : conditional.false_branch()) {
      statement->Visit(&falseVisitor);
    }
    int trueStatements = trueVisitor.NumberOfStatements();
    int falseStatements = falseVisitor.NumberOfStatements();
    conditional.guard().Visit(this);
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(trueStatements + labelNum_ + 1),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
    for (auto& statement : conditional.true_branch()) {
      statement->Visit(this);
    }
    newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(falseStatements + labelNum_),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
    for (auto& statement : conditional.false_branch()) {
      statement->Visit(this);
    }
  }
  void VisitLoop(const Loop& loop) {
    IrGenVisitor blockvisitor;
    IrGenVisitor guardVisitor;
    loop.guard().Visit(&guardVisitor);
    int startLabelNum = labelNum_;
    for (auto& statement : loop.body()) {
      statement->Visit((&blockvisitor));
    }
    int bodyStatements = blockvisitor.NumberOfStatements();
    loop.guard().Visit(this);
    StatementNode *newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(bodyStatements + labelNum_ + 1),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
    for (auto& statement : loop.body()) {
      statement->Visit(this);
    }
    newtail = new StatementNode(
      new Label(labelNum_++),
      new Label(startLabelNum),
      new Operator(Operator::kGoto),
      nullptr,
      nullptr,
      nullptr);
    AddToEnd(newtail);
  }

  StatementNode* GetIR() { return head_; }
  void AddToEnd(StatementNode* newtail) {
    if (head_ == nullptr && tail_ == nullptr) {
      head_ = newtail;
      tail_ = newtail;
      while (tail_->GetNext() != nullptr) tail_ = tail_->GetNext();
      return;
    }
    tail_->GetNext() = newtail;
    tail_ = tail_->GetNext();
    while (tail_->GetNext() != nullptr) tail_ = tail_->GetNext();
  }

  void PrintIR() {
    StatementNode* itor = head_;
    std::cout << "/*#### Start of IR ####\n\n";
    while (itor != nullptr) {
      itor->Print();
      itor = itor->GetNext();
      std::cout << endl;
    }
    std::cout << "\n#### End of IR ####*/\n\n";
  }

  int NumberOfStatements() {
    StatementNode* itor = head_;
    int statementCount = 0;
    while (itor != nullptr) {
      itor = itor->GetNext();
      statementCount++;
    }
    return statementCount;
  }
  int NumberOfMainVars() { return mainVars_; }

 private:
  StatementNode * head_ = nullptr;
  StatementNode* tail_ = nullptr;
  int labelNum_ = 0;
  int register_number_ = 1;
  std::vector<Operand*> stack_;
  int mainVars_ = 0;
  std::vector<string> paramVariables_;
  std::vector<string> localVariables_;
  bool scanningParams_ = false;
};

}  // namespace backend
}  // namespace cs160

#endif  // BACKEND_LOWERER_V4_H_
