// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V4_H_
#define BACKEND_LOWERER_V4_H_

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v4.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v4.h"
#include <algorithm>


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
      void VisitIntegerExpr(const IntegerExpr& exp) override {  }
      void VisitVariableExpr(const VariableExpr& exp) override {
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

      void VisitAddExpr(const AddExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitSubtractExpr(const SubtractExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitMultiplyExpr(const MultiplyExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitDivideExpr(const DivideExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitLessThanExpr(const LessThanExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitGreaterThanExpr(const GreaterThanExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitEqualToExpr(const EqualToExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitLogicalAndExpr(const LogicalAndExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitLogicalOrExpr(const LogicalOrExpr& exp) override {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
      }

      void VisitLogicalNotExpr(const LogicalNotExpr& exp) override {
        exp.operand().Visit(this);
      }

      void VisitAssignment(const Assignment& assignment) override {
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

      void VisitConditional(const Conditional& conditional) override {
        conditional.guard().Visit(this);
        for (auto& statement : conditional.true_branch()) {
          statement->Visit(this);
        }
        for (auto& statement : conditional.false_branch()) {
          statement->Visit(this);
        }
      }

      void VisitLoop(const Loop& loop) override {
        loop.guard().Visit(this);
        for (auto& statement : loop.body()) {
          statement->Visit(this);
        }
      }

      void VisitProgram(const Program& program) override {
        for (auto& statement : program.statements()) {
          statement->Visit(this);
        }
        program.arithmetic_exp().Visit(this);
      }
      void VisitFunctionCall(const FunctionCall& call) override {
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

      void VisitFunctionDef(const FunctionDef& def) override { }
      void ScanningParams(bool scanningParams) { scanningParams_ = scanningParams; }
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
      void VisitVariableExpr(const VariableExpr& exp) {
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
      }
      void VisitProgram(const Program& program) {
        for (auto& def : program.function_defs()) { def->Visit(this); }
        CountVisitor varCount;
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
        localVariables_.clear();
      }
      void VisitFunctionCall(const FunctionCall& call) override {
        int numArgs = call.arguments().size();
        for (auto& arg : call.arguments()) { arg->Visit(this);
        StatementNode* newhead = new StatementNode(
          new Label(labelNum_++),
          new Register(register_number_-1),
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
      void VisitFunctionDef(const FunctionDef& def) override {
        CountVisitor varsCounter;
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
      int labelNum_ = 1;
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
