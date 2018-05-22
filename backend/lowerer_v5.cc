// Copyright(c) 2018, Team Chant

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v5.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v5.h"
#include "backend/lowerer_v5.h"
#include <algorithm>




using cs160::abstract_syntax::version_5::AstVisitor;
using cs160::abstract_syntax::version_5::ArithmeticExpr;
using cs160::abstract_syntax::version_5::Assignable;
using cs160::abstract_syntax::version_5::AddExpr;
using cs160::abstract_syntax::version_5::SubtractExpr;
using cs160::abstract_syntax::version_5::MultiplyExpr;
using cs160::abstract_syntax::version_5::DivideExpr;
using cs160::abstract_syntax::version_5::IntegerExpr;
using cs160::abstract_syntax::version_5::VariableExpr;
using cs160::abstract_syntax::version_5::Dereference;
using cs160::abstract_syntax::version_5::LessThanExpr;
using cs160::abstract_syntax::version_5::LessThanEqualToExpr;
using cs160::abstract_syntax::version_5::GreaterThanExpr;
using cs160::abstract_syntax::version_5::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_5::EqualToExpr;
using cs160::abstract_syntax::version_5::LogicalAndExpr;
using cs160::abstract_syntax::version_5::LogicalOrExpr;
using cs160::abstract_syntax::version_5::LogicalNotExpr;
using cs160::abstract_syntax::version_5::Statement;
using cs160::abstract_syntax::version_5::AssignmentFromArithExp;
using cs160::abstract_syntax::version_5::AssignmentFromNewTuple;
using cs160::abstract_syntax::version_5::Conditional;
using cs160::abstract_syntax::version_5::Loop;
using cs160::abstract_syntax::version_5::FunctionCall;
using cs160::abstract_syntax::version_5::FunctionDef;
using cs160::abstract_syntax::version_5::Program;
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
    void VarCountVisitor::VisitIntegerExpr(const IntegerExpr& exp) {  }
    void VarCountVisitor::VisitVariableExpr(const VariableExpr& exp) {
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (exp.name())) != paramVariables_.end();
      if (foundinParams) {}
      else {
        if (scanningParams_ == false) {
          bool found = std::find(localVariables_.begin(), localVariables_.end(), (exp.name())) != localVariables_.end();
          if (!found) { localVariables_.push_back(exp.name()); }
          else {}
        }
        else if (scanningParams_ == true) {
          bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (exp.name())) != paramVariables_.end();
          if (!found) { paramVariables_.push_back(exp.name()); }
          else {}
        }
      }
    }

    void VarCountVisitor::VisitDereference(const Dereference& exp) {
      //!!
    }

    void VarCountVisitor::VisitAssignmentFromArithExp(
      const AssignmentFromArithExp& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
      count_++;
    }

    void VarCountVisitor::VisitAssignmentFromNewTuple(
      const AssignmentFromNewTuple& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
      count_++;
    }

    void VarCountVisitor::VisitAddExpr(const AddExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitDivideExpr(const DivideExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitLessThanExpr(const LessThanExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitGreaterThanExpr(const GreaterThanExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitEqualToExpr(const EqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitLogicalAndExpr(const LogicalAndExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitLogicalOrExpr(const LogicalOrExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }

    void VarCountVisitor::VisitLogicalNotExpr(const LogicalNotExpr& exp) {
      exp.operand().Visit(this);
    }
    /*
    void VisitAssignment(const Assignment& assignment) {
    assignment.rhs().Visit(this);
    bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (assignment.lhs().name())) != paramVariables_.end();
    if (foundinParams) {}
    else {
    if (scanningParams_ == false) {
    bool found = std::find(localVariables_.begin(), localVariables_.end(), (assignment.lhs().name())) != localVariables_.end();
    if (!found) { localVariables_.push_back(assignment.lhs().name()); }
    else {}
    }
    else if (scanningParams_ == true) {
    bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (assignment.lhs().name())) != paramVariables_.end();
    if (!found) { paramVariables_.push_back(assignment.lhs().name()); }
    else {}
    }
    }
    }
    */

    void VarCountVisitor::VisitConditional(const Conditional& conditional) {
      conditional.guard().Visit(this);
      for (auto& statement : conditional.true_branch()) {
        statement->Visit(this);
      }
      for (auto& statement : conditional.false_branch()) {
        statement->Visit(this);
      }
    }

    void VarCountVisitor::VisitLoop(const Loop& loop) {
      loop.guard().Visit(this);
      for (auto& statement : loop.body()) {
        statement->Visit(this);
      }
    }

    void VarCountVisitor::VisitProgram(const Program& program) {
      for (auto& statement : program.statements()) {
        statement->Visit(this);
      }
      program.arithmetic_exp().Visit(this);
    }
    void VarCountVisitor::VisitFunctionCall(const FunctionCall& call) {
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (call.lhs().name())) != paramVariables_.end();
      if (foundinParams) {}
      else {
        if (scanningParams_ == false) {
          bool found = std::find(localVariables_.begin(), localVariables_.end(), (call.lhs().name())) != localVariables_.end();
          if (!found) { localVariables_.push_back(call.lhs().name()); }
          else {}
        }
        else if (scanningParams_ == true) {
          bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (call.lhs().name())) != paramVariables_.end();
          if (!found) { paramVariables_.push_back(call.lhs().name()); }
          else {}
        }
      }
    }

    void VarCountVisitor::VisitFunctionDef(const FunctionDef& def) { }
    void VarCountVisitor::ScanningParams(bool scanningParams) { scanningParams_ = scanningParams; }
    int VarCountVisitor::LocalVars() { return localVariables_.size(); }
    int VarCountVisitor::ParamVars() { return paramVariables_.size(); }



    void IrGenVisitor::VisitIntegerExpr(const IntegerExpr& exp) {
      stack_.push_back(new Register(register_number_));
      StatementNode* newhead = new StatementNode(
        new Label(labelNum_++),
        new Register(register_number_++),
        new Operator(Operator::kRegister),
        nullptr,
        new Constant(exp.value()),
        nullptr
      );
      AddToEnd(newhead);
    }
    void IrGenVisitor::VisitVariableExpr(const VariableExpr& exp) {
      stack_.push_back(new Register(register_number_));
      int pos;
      int stackOffset;
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (exp.name())) != paramVariables_.end();
      if (foundinParams) {
        pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), exp.name()));
        stackOffset = 1 * ((pos + 2) * 8);
        stack_.back()->SetStackOffset(stackOffset);
      }
      else {
        if (scanningParams_ == false) {
          bool found = std::find(localVariables_.begin(), localVariables_.end(), (exp.name())) != localVariables_.end();
          if (!found) { localVariables_.push_back(exp.name()); }
          else {}
          pos = std::distance(localVariables_.begin(), std::find(localVariables_.begin(), localVariables_.end(), exp.name()));
          stackOffset = -1 * ((pos + 1) * 8);
          stack_.back()->SetStackOffset(stackOffset);
        }
        else if (scanningParams_ == true) {
          if (!foundinParams) { paramVariables_.push_back(exp.name()); }
          else {}
          pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), exp.name()));
          stackOffset = 1 * ((pos + 2) * 8);
          stack_.back()->SetStackOffset(stackOffset);
        }
      }
      if (!scanningParams_) {
        StatementNode* newhead = new StatementNode(
          new Label(labelNum_++),
          new Register(register_number_++),
          new Operator(Operator::kRegister),
          nullptr,
          new Variable(exp.name()),
          nullptr
        );
        newhead->GetOp2()->SetStackOffset(stackOffset);
        AddToEnd(newhead);
      }
    }
    void IrGenVisitor::VisitDereference(const Dereference& exp) {
      //!!
    }

    void IrGenVisitor::VisitAssignmentFromArithExp(
      const AssignmentFromArithExp& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
    }

    void IrGenVisitor::VisitAssignmentFromNewTuple(
      const AssignmentFromNewTuple& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
    }
    /*
    void VisitAssignment(const Assignment& assignment) {

    int pos;
    int stackOffset;
    bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (assignment.lhs().name())) != paramVariables_.end();
    if (foundinParams) {
    pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), assignment.lhs().name()));
    stackOffset = 1 * ((pos + 2) * 8);
    }
    else {
    if (scanningParams_ == false) {
    bool found = std::find(localVariables_.begin(), localVariables_.end(), (assignment.lhs().name())) != localVariables_.end();
    if (!found) { localVariables_.push_back(assignment.lhs().name()); }
    else {}
    pos = std::distance(localVariables_.begin(), std::find(localVariables_.begin(), localVariables_.end(), assignment.lhs().name()));
    stackOffset = -1 * ((pos + 1) * 8);
    }
    else if (scanningParams_ == true) {
    bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (assignment.lhs().name())) != paramVariables_.end();
    if (!found) {
    paramVariables_.push_back(assignment.lhs().name());
    }
    else {}
    pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), assignment.lhs().name()));
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
    }*/
    void IrGenVisitor::VisitAddExpr(const AddExpr& exp) {
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

    void IrGenVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
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

    void IrGenVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
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

    void IrGenVisitor::VisitDivideExpr(const DivideExpr& exp) {
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

    void IrGenVisitor::VisitProgram(const Program& program) {
      for (auto& def : program.function_defs()) { def->Visit(this); }
      VarCountVisitor varCount;
      varCount.ScanningParams(false);
      for (auto& statement : program.statements()) { statement->Visit(&varCount); }
      mainVars_ = varCount.LocalVars();
      StatementNode* newhead = new StatementNode(
        new Label(labelNum_++),
        nullptr,
        new Operator(Operator::kProgramStart),
        nullptr,
        new Constant(mainVars_),
        nullptr
      );
      AddToEnd(newhead);
      for (auto& statement : program.statements()) { statement->Visit(this); }
      program.arithmetic_exp().Visit(this);
      newhead = new StatementNode(
        new Label(labelNum_++),
        new Register(register_number_ - 1),
        new Operator(Operator::kReturn),
        nullptr,
        nullptr,
        nullptr
      );
      AddToEnd(newhead);
      localVariables_.clear();
    }
    void IrGenVisitor::VisitFunctionCall(const FunctionCall& call) {
      int numArgs = call.arguments().size();
      for (auto& arg : call.arguments()) {
        arg->Visit(this);
        StatementNode* newhead = new StatementNode(
          new Label(labelNum_++),
          new Register(register_number_ - 1),
          new Operator(Operator::kParam),
          nullptr,
          nullptr,
          nullptr
        );
        AddToEnd(newhead);
      }
      int pos;
      int stackOffset;
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (call.lhs().name())) != paramVariables_.end();
      if (foundinParams) {
        pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), call.lhs().name()));
        stackOffset = 1 * ((pos + 2) * 8);
      }
      else {
        if (scanningParams_ == false) {
          bool found = std::find(localVariables_.begin(), localVariables_.end(), (call.lhs().name())) != localVariables_.end();
          if (!found) { localVariables_.push_back(call.lhs().name()); }
          else {}
          pos = std::distance(localVariables_.begin(), std::find(localVariables_.begin(), localVariables_.end(), call.lhs().name()));
          stackOffset = -1 * ((pos + 1) * 8);
        }
        else if (scanningParams_ == true) {
          bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (call.lhs().name())) != paramVariables_.end();
          if (!found) {
            paramVariables_.push_back(call.lhs().name());
          }
          else {}
          pos = std::distance(paramVariables_.begin(), std::find(paramVariables_.begin(), paramVariables_.end(), call.lhs().name()));
          stackOffset = 1 * ((pos + 2) * 8);
        }
      }
      StatementNode* newhead = new StatementNode(
        new Label(labelNum_++),
        new Variable(call.callee_name()),
        new Operator(Operator::kCall),
        new Variable(call.lhs().name()),
        new Constant(numArgs),
        nullptr);
      newhead->GetTarget()->SetStackOffset(stackOffset);
      AddToEnd(newhead);
    }
    void IrGenVisitor::VisitFunctionDef(const FunctionDef& def) {
      VarCountVisitor varsCounter;
      varsCounter.ScanningParams(true);
      for (auto& param : def.parameters()) { param->Visit(&varsCounter); }
      varsCounter.ScanningParams(false);
      for (auto& statement : def.function_body()) { statement->Visit(&varsCounter); }
      int numLocalVar = varsCounter.LocalVars();
      StatementNode*newhead = new StatementNode(
        new Label(labelNum_++),
        new Variable(def.function_name()),
        new Operator(Operator::kFuncBegin),
        nullptr,
        new Constant(numLocalVar),
        nullptr);
      AddToEnd(newhead);
      scanningParams_ = true;
      for (auto& param : def.parameters()) { param->Visit(this); }
      scanningParams_ = false;
      for (auto& statement : def.function_body()) { statement->Visit(this); }
      def.retval().Visit(this);
      newhead = new StatementNode(
        new Label(labelNum_++),
        new Register(register_number_ - 1),
        new Operator(Operator::kReturn),
        nullptr,
        nullptr,
        nullptr
      );
      AddToEnd(newhead);
      newhead = new StatementNode(
        new Label(labelNum_++),
        new Variable(def.function_name()),
        new Operator(Operator::kFuncEnd),
        nullptr,
        new Constant(numLocalVar),
        nullptr);
      AddToEnd(newhead);
      localVariables_.clear();
      paramVariables_.clear();
    }
    void IrGenVisitor::VisitLessThanExpr(const LessThanExpr& exp) {
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
    void IrGenVisitor::VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {
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
    void IrGenVisitor::VisitGreaterThanExpr(const GreaterThanExpr& exp) {
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
    void IrGenVisitor::VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) {
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
    void IrGenVisitor::VisitEqualToExpr(const EqualToExpr& exp) {
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
    void IrGenVisitor::VisitLogicalAndExpr(const LogicalAndExpr& exp) {
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
    void IrGenVisitor::VisitLogicalOrExpr(const LogicalOrExpr& exp) {

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
    void IrGenVisitor::VisitLogicalNotExpr(const LogicalNotExpr& exp) {
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
    void IrGenVisitor::VisitConditional(const Conditional& conditional) {
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
    void IrGenVisitor::VisitLoop(const Loop& loop) {
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
    void IrGenVisitor::AddToEnd(StatementNode* newtail) {
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
    

    void IrGenVisitor::PrintIR() {
      StatementNode* itor = head_;
      std::cout << "/*#### Start of IR ####\n\n";
      while (itor != nullptr) {
        itor->Print();
        itor = itor->GetNext();
        std::cout << endl;
      }
    }

    


    int IrGenVisitor::NumberOfStatements() {
      StatementNode* itor = head_;
      int statementCount = 0;
      while (itor != nullptr) {
        itor = itor->GetNext();
        statementCount++;
      }
      return statementCount;
    }


  }
}
