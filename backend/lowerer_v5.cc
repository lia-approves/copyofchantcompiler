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
      AddVariable(exp.name());
    }
    void VarCountVisitor::VisitDereference(const Dereference& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
    }
    void VarCountVisitor::VisitAssignmentFromArithExp(
      const AssignmentFromArithExp& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
    }
    void VarCountVisitor::VisitAssignmentFromNewTuple(
      const AssignmentFromNewTuple& assignment) {
      assignment.lhs().Visit(this);
      assignment.rhs().Visit(this);
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
      AddVariable(call.lhs().name());
    }
    void VarCountVisitor::VisitFunctionDef(const FunctionDef& def) { }
    void VarCountVisitor::ScanningParams(bool scanningParams) { readingParams_ = scanningParams; }
    int VarCountVisitor::LocalVars() { return localVariables_.size(); }
    int VarCountVisitor::ParamVars() { return paramVariables_.size(); }
    void VarCountVisitor::AddVariable(string variable) {
      bool foundinParams = std::find(paramVariables_.begin(), paramVariables_.end(), (variable)) != paramVariables_.end();
      if (foundinParams) {}
      else {
        if (readingParams_ == false) {
          bool found = std::find(localVariables_.begin(), localVariables_.end(), (variable)) != localVariables_.end();
          if (!found) { localVariables_.push_back(variable); }
          else {}
        }
        else if (readingParams_ == true) {
          bool found = std::find(paramVariables_.begin(), paramVariables_.end(), (variable)) != paramVariables_.end();
          if (!found) { paramVariables_.push_back(variable); }
          else {}
        }
      }
    }


    void IrGenVisitor::VisitIntegerExpr(const IntegerExpr& exp) { //push value of int
      StatementNode* newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_),
        new Operator(Operator::kPushValueOfInteger),
        nullptr,
        new Constant(exp.value()),
        nullptr
      );
      AddToEnd(newhead);
      ir_stack_.push_back(new Register(register_number_++));
    }
    void IrGenVisitor::VisitVariableExpr(const VariableExpr& exp) { 
      bool returnAddress = false;
      if (requestAddressFromNextNode == true) returnAddress = true; //read request
      StatementNode* newhead;
      if (!readingParams_) {
        if (returnAddress == true) {   //push value or address depending on request from parent node
          newhead = new StatementNode(
            make_unique<Label>(labelNum_++),
            new Register(register_number_),
            new Operator(Operator::kPushAddressOfVariable),
            nullptr,
            new Variable(exp.name()),
            nullptr
          );
        }
        else if (returnAddress == false) {
          newhead = new StatementNode(
            make_unique<Label>(labelNum_++),
            new Register(register_number_),
            new Operator(Operator::kPushValueOfVariable),
            nullptr,
            new Variable(exp.name()),
            nullptr
          );
        }
        AddToEnd(newhead);
      }
      else if (readingParams_) {
        newhead = new StatementNode(
          make_unique<Label>(labelNum_++),
          new Variable(exp.name()),
          new Operator(Operator::kParam),
          nullptr,
          nullptr,
          nullptr
        );
        AddToEnd(newhead);
      }
      ir_stack_.push_back(new Register(register_number_++));
    }
    void IrGenVisitor::VisitDereference(const Dereference& exp) { 
      bool returnAddress = false;
      if (requestAddressFromNextNode == true) returnAddress = true; //read request
      requestAddressFromNextNode = true;   // we need address from lsh, request adress
      exp.lhs().Visit(this);
      requestAddressFromNextNode = false; // need just value from rhs
      exp.rhs().Visit(this);
      Operand* index = ir_stack_.back(); // index is at top of stack(lhs), adress is at 2nd to top(lhs)
      ir_stack_.pop_back();
      Operand* address = ir_stack_.back(); //ex: x[4] x is address, 4 is index
      ir_stack_.pop_back();
      if (returnAddress == true) {  //push value or address depending on request from parent node
        StatementNode* newhead = new StatementNode(
          make_unique<Label>(labelNum_++),
          new Register(register_number_),
          new Operator(Operator::kPushAddressOfDereference),
          address,
          index,
          nullptr
        );
        AddToEnd(newhead);
      }
      else if (returnAddress == false) {
        StatementNode* newhead = new StatementNode(
          make_unique<Label>(labelNum_++),
          new Register(register_number_),
          new Operator(Operator::kPushValueOfDereference),
          address,
          index,
          nullptr
        );
        AddToEnd(newhead);
      }
      ir_stack_.push_back(new Register(register_number_++));
    }
    void IrGenVisitor::VisitAssignmentFromArithExp(
      const AssignmentFromArithExp& assignment) {
      requestAddressFromNextNode = true; //need address from lhs
      assignment.lhs().Visit(this);
      requestAddressFromNextNode = false; //need value from rhs
      assignment.rhs().Visit(this);
      Operand* value = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* address = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode* newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        address,
        new Operator(Operator::kAssignmentFromArithExp),
        nullptr,
        value,
        nullptr
      );
      AddToEnd(newhead);
    }
    void IrGenVisitor::VisitAssignmentFromNewTuple(const AssignmentFromNewTuple& assignment) {
      requestAddressFromNextNode = true; //address from lhs
      assignment.lhs().Visit(this);
      requestAddressFromNextNode = false; //value from rhs
      assignment.rhs().Visit(this);
      Operand* tupleSize = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* tupleVar = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
        tupleVar,
        new Operator(Operator::kAssignmentFromNewTuple),
        nullptr,
        tupleSize,
        nullptr);
      AddToEnd(newtail);
    }
    void IrGenVisitor::VisitAddExpr(const AddExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_),
        new Operator(Operator::kAdd),
        op1,
        op2,
        nullptr);
      AddToEnd(newtail);
      ir_stack_.push_back(new Register(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_),
        new Operator(Operator::kSubtract),
        op1,
        op2,
        nullptr);
      AddToEnd(newtail);
      ir_stack_.push_back(new Register(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_),
        new Operator(Operator::kMultiply),
        op1,
        op2,
        nullptr);
      AddToEnd(newtail);
      ir_stack_.push_back(new Register(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitDivideExpr(const DivideExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_),
        new Operator(Operator::kDivide),
        op1,
        op2,
        nullptr);
      AddToEnd(newtail);
      ir_stack_.push_back(new Register(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitProgram(const Program& program) {
      for (auto& def : program.function_defs()) { def->Visit(this); } //we visit func def firs they go at top of assmbly
      VarCountVisitor varCount;
      varCount.ScanningParams(false);
      for (auto& statement : program.statements()) { statement->Visit(&varCount); }
      mainVars_ = varCount.LocalVars(); //we find out how many local vars we need
      StatementNode* newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        nullptr,
        new Operator(Operator::kProgramStart), //this is so we know how many local vars to alocate on the stack
        nullptr,
        new Constant(mainVars_),
        nullptr
      );
      AddToEnd(newhead);
      for (auto& statement : program.statements()) { statement->Visit(this); }
      program.arithmetic_exp().Visit(this); //evaluate ae
      newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_ - 1),
        new Operator(Operator::kReturn),
        nullptr,
        nullptr,
        nullptr
      );
      AddToEnd(newhead);
      newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        nullptr,
        new Operator(Operator::kProgramEnd),
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
        arg->Visit(this); //visit args place on stack need to fix this its backwards
        StatementNode* newhead = new StatementNode(
          make_unique<Label>(labelNum_++),
          new Register(register_number_ - 1),
          new Operator(Operator::kArgument),
          nullptr,
          nullptr,
          nullptr
        );
        AddToEnd(newhead);
      } 
      StatementNode* newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Variable(call.callee_name()),
        new Operator(Operator::kCall),
        new Variable(call.lhs().name()),
        new Constant(numArgs),
        nullptr);
      AddToEnd(newhead);
    }
    void IrGenVisitor::VisitFunctionDef(const FunctionDef& def) { 
      VarCountVisitor varsCounter;// we count number of params and local vars
      varsCounter.ScanningParams(true); // count params first we dont want to redeclare var if its in params already
      for (auto& param : def.parameters()) { param->Visit(&varsCounter); }
      varsCounter.ScanningParams(false);
      for (auto& statement : def.function_body()) { statement->Visit(&varsCounter); }
      int numLocalVar = varsCounter.LocalVars(); 
      StatementNode*newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Variable(def.function_name()),
        new Operator(Operator::kFuncBegin), //call to crate func
        nullptr,
        new Constant(numLocalVar),
        nullptr);
      AddToEnd(newhead);
      readingParams_ = true;
      for (auto& param : def.parameters()) { param->Visit(this); }
      readingParams_ = false;
      for (auto& statement : def.function_body()) { statement->Visit(this); }
      def.retval().Visit(this);
      newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
        new Register(register_number_ - 1),
        new Operator(Operator::kReturn),
        nullptr,
        nullptr,
        nullptr
      );
      AddToEnd(newhead);
      newhead = new StatementNode(
        make_unique<Label>(labelNum_++),
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
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
      Operand* op2 = ir_stack_.back();
      ir_stack_.pop_back();
      Operand* op1 = ir_stack_.back();
      ir_stack_.pop_back();
      StatementNode *newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
        new Label(labelNum_ + 1),
        new Operator(Operator::kGoto),
        nullptr,
        nullptr,
        nullptr);
      AddToEnd(newtail);
      newtail = new StatementNode(
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        make_unique<Label>(labelNum_++),
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
        return;
      }
      tail_->GetNext() = newtail;
      tail_ = tail_->GetNext();
      return;
    }
    void IrGenVisitor::PrintIR() {
      StatementNode* itor = head_;
      std::cout << "#### Start of IR ####" << endl;
      while (itor != nullptr) {
        itor->Print();
        itor = itor->GetNext();
        std::cout << endl;
      }
      std::cout << "#### END of IR ####" << endl;
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
