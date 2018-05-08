// Copyright(c) 2018, Team Chant

#ifndef BACKEND_LOWERER_V3_H_
#define BACKEND_LOWERER_V3_H_

#include <sstream>
#include <string>
#include <vector>
#include "backend/ir_v3.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v3.h"


using cs160::abstract_syntax::version_3::IntegerExpr;
using cs160::abstract_syntax::version_3::ArithmeticBinaryOperatorExpr;
using cs160::abstract_syntax::version_3::AddExpr;
using cs160::abstract_syntax::version_3::SubtractExpr;
using cs160::abstract_syntax::version_3::MultiplyExpr;
using cs160::abstract_syntax::version_3::DivideExpr;
using cs160::abstract_syntax::version_3::AstNode;
using cs160::abstract_syntax::version_3::AstVisitor;
using cs160::abstract_syntax::version_3::VariableExpr;
using cs160::abstract_syntax::version_3::Assignment;
using cs160::abstract_syntax::version_3::Program;
using cs160::abstract_syntax::version_3::LessThanExpr;
using cs160::abstract_syntax::version_3::LessThanEqualToExpr;
using cs160::abstract_syntax::version_3::GreaterThanExpr;
using cs160::abstract_syntax::version_3::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_3::EqualToExpr;
using cs160::abstract_syntax::version_3::LogicalAndExpr;
using cs160::abstract_syntax::version_3::LogicalOrExpr;
using cs160::abstract_syntax::version_3::LogicalNotExpr;
using cs160::abstract_syntax::version_3::Conditional;
using cs160::abstract_syntax::version_3::Loop;
using cs160::backend::ir::StatementNode;
using cs160::backend::ir::Constant;
using cs160::backend::ir::Label;
using cs160::backend::ir::Operator;
using cs160::backend::ir::Register;
using cs160::backend::ir::Operand;
using cs160::backend::ir::Variable;
using std::cout;


namespace cs160 {
  namespace backend {
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

      void VisitIntegerExpr(const IntegerExpr& exp) {
        stack_.push_back(new Constant(exp.value()));
      }

      void VisitAddExpr(const AddExpr& exp) {
        exp.lhs().Visit(this);
        exp.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        Operand* op1 = stack_.back();
        StatementNode *newtail = new StatementNode(new Label(labelNum_++),
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
        StatementNode *newtail = new StatementNode(new Label(labelNum_++),
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
        StatementNode *newtail = new StatementNode(new Label(labelNum_++),
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
        StatementNode *newtail = new StatementNode(new Label(labelNum_++),
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

      void VisitVariableExpr(const VariableExpr& exp) {
        stack_.push_back(new Variable(exp.name()));
      }
      void VisitAssignment(const Assignment& assignment) {
        assignment.rhs().Visit(this);
        Operand* op2 = stack_.back();
        stack_.pop_back();
        StatementNode *newtail = new StatementNode(new Label(labelNum_++),
          new Variable(assignment.lhs().name()),
          new Operator(Operator::kAssign),
          nullptr,
          op2,
          nullptr);
        AddToEnd(newtail);
        stack_.push_back(new Register(register_number_));
      }
      void VisitProgram(const Program& program) {
        for (auto& statement : program.statements()) {
          statement->Visit(this);
        }
        program.arithmetic_exp().Visit(this);

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
          //new Label(labelNum_ + numGuard_+numTrue_),
          new Operator(Operator::kGoto),
          nullptr,
          nullptr,
          nullptr);
        AddToEnd(newtail);
        //numGuard_  -= 2;
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
        IrGenVisitor guardVisitor;
        int startLabelNum = labelNum_;
        for (auto& statement : conditional.true_branch()) {
          statement->Visit(&trueVisitor);
        }
        for (auto& statement : conditional.false_branch()) {
          statement->Visit(&falseVisitor);
        }
        conditional.guard().Visit(&guardVisitor);
        int trueStatements =+ trueVisitor.NumberOfStatements();
        int falseStatements =+ falseVisitor.NumberOfStatements();
        int guardStatements =+ guardVisitor.NumberOfStatements();
        numGuard_ = guardStatements;
        numTrue_ = trueStatements;
        numFalse_ = falseStatements;
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
          new Label(falseStatements + labelNum_ ),
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
        int guardStatements = guardVisitor.NumberOfStatements();

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

        std::cout << "#### Sart of IR ####\n\n";

        int statementNum = 1;
        while (itor != nullptr) {
          itor->Print();
          itor = itor->GetNext();
          std::cout << endl;
        }
        std::cout << "\n#### End of IR ####\n\n";
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

    private:
      StatementNode * head_ = nullptr;
      StatementNode* tail_ = nullptr;
      int labelNum_ = 1;
      std::vector<Operand*> stack_;
      int register_number_ = 1;
      int numGuard_ = 0;
      int numTrue_ = 0;
      int numFalse_ = 0;
    };

    class GuardVisitor : IrGenVisitor {
    public:
      GuardVisitor() { IrGenVisitor(); }
      int NumberOfStatements();
      void VisitLogicalAndExpr(const LogicalAndExpr& exp) {
        IrGenVisitor::VisitLogicalAndExpr(exp);
        numberOfStatements_++;
      }
      void VisitLogicalOrExpr(const LogicalOrExpr& exp) {
        IrGenVisitor::VisitLogicalOrExpr(exp);
        numberOfStatements_++;
      }
      void VisitLogicalNotExpr(const LogicalAndExpr& exp) {
        // to 
      }
    private:
      int numberOfStatements_ = 0;
    };
  }  // namespace backend
}  // namespace cs160

#endif  // BACKEND_LOWERER_V3_H_
