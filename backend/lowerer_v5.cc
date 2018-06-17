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
using cs160::backend::Instruction;
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
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_),
        make_unique<Instruction>(Instruction::kValueOfInteger),
        nullptr,
        make_unique<Constant>(exp.value()));
      AddToEnd(newhead);
      ir_stack_.push_back(make_unique<Register>(register_number_++));
    }
    void IrGenVisitor::VisitVariableExpr(const VariableExpr& exp) {
      bool returnAddress = false;
      if (requestAddressFromNextNode == true) returnAddress = true; //read request
      std::shared_ptr <StatementNode>newhead;
      if (!readingParams_) {
        if (returnAddress == true) {   //push value or address depending on request from parent node
          newhead = std::make_shared< StatementNode>(
            make_unique<Label>(labelNum_++),
            make_unique<Register>(register_number_),
            make_unique<Instruction>(Instruction::kAddressOfVariable),
            nullptr,
            make_unique<Variable>(exp.name()));
        }
        else if (returnAddress == false) {
          newhead = std::make_shared< StatementNode>(
            make_unique<Label>(labelNum_++),
            make_unique<Register>(register_number_),
            make_unique<Instruction>(Instruction::kValueOfVariable),
            nullptr,
            make_unique<Variable>(exp.name()));
        }
        AddToEnd(std::move(newhead));
      }
      else if (readingParams_) {
        newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          make_unique<Variable>(exp.name()),
          make_unique<Instruction>(Instruction::kParam),
          nullptr,
          nullptr);
        AddToEnd(std::move(newhead));
      }
      ir_stack_.push_back(make_unique<Register>(register_number_++));
    }
    void IrGenVisitor::VisitDereference(const Dereference& exp) {
      bool returnAddress = false;
      if (requestAddressFromNextNode == true) returnAddress = true; //read request
      requestAddressFromNextNode = true;   // we need address from lsh, request adress
      exp.lhs().Visit(this);
      requestAddressFromNextNode = false; // need just value from rhs
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> index = std::move(ir_stack_.back()); // index is at top of stack(lhs), adress is at 2nd to top(lhs)
      ir_stack_.pop_back();
      std::unique_ptr<Operand> address = std::move(ir_stack_.back()); //ex: x[4] x is address, 4 is index
      ir_stack_.pop_back();
      if (returnAddress == true) {  //push value or address depending on request from parent node
        std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          make_unique<Register>(register_number_),
          make_unique<Instruction>(Instruction::kAddressOfDereference),
          std::move(address),
          std::move(index));
        AddToEnd(std::move(newhead));
      }
      else if (returnAddress == false) {
        std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          make_unique<Register>(register_number_),
          make_unique<Instruction>(Instruction::kValueOfDereference),
          std::move(address),
          std::move(index));
        AddToEnd(std::move(newhead));
      }
      ir_stack_.push_back(make_unique<Register>(register_number_++));
    }
    void IrGenVisitor::VisitAssignmentFromArithExp(
      const AssignmentFromArithExp& assignment) {
      assignment.rhs().Visit(this);
      if (const VariableExpr* variable = dynamic_cast<const VariableExpr*>(&assignment.lhs())) {
        
        std::unique_ptr<Operand> value = std::move(ir_stack_.back());
        ir_stack_.pop_back();
        std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          make_unique<Variable>(variable->name()),
          make_unique<Instruction>(Instruction::kAssignmentToVariable),
          nullptr,
          std::move(value));
        AddToEnd(std::move(newhead));
      }
      else {
        requestAddressFromNextNode = true; //need address from lhs
        assignment.lhs().Visit(this);
        requestAddressFromNextNode = false; //need value from rhs
        std::unique_ptr<Operand> value = std::move(ir_stack_.back());
        ir_stack_.pop_back();
        std::unique_ptr<Operand> address = std::move(ir_stack_.back());
        ir_stack_.pop_back();
        std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          std::move(value),
          make_unique<Instruction>(Instruction::kAssignmentFromArithExp),
          nullptr,
          std::move(address));
        AddToEnd(std::move(newhead));
      }
    }
    void IrGenVisitor::VisitAssignmentFromNewTuple(const AssignmentFromNewTuple& assignment) {
      requestAddressFromNextNode = true; //address from lhs
      assignment.lhs().Visit(this);
      requestAddressFromNextNode = false; //value from rhs
      assignment.rhs().Visit(this);
      std::unique_ptr<Operand> tupleSize = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> tupleVar = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        std::move(tupleVar),
        make_unique<Instruction>(Instruction::kAssignmentFromNewTuple),
        nullptr,
        std::move(tupleSize));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitAddExpr(const AddExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_),
        make_unique<Instruction>(Instruction::kAdd),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
      ir_stack_.push_back(make_unique<Register>(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_),
        make_unique<Instruction>(Instruction::kSubtract),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
      ir_stack_.push_back(make_unique<Register>(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_),
        make_unique<Instruction>(Instruction::kMultiply),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
      ir_stack_.push_back(make_unique<Register>(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitDivideExpr(const DivideExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_),
        make_unique<Instruction>(Instruction::kDivide),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
      ir_stack_.push_back(make_unique<Register>(register_number_++)); //push result to stack
    }
    void IrGenVisitor::VisitProgram(const Program& program) {
      for (auto& def : program.function_defs()) { def->Visit(this); } //we visit func def firs they go at top of assmbly
      VarCountVisitor varCount;
      varCount.ScanningParams(false);
      for (auto& statement : program.statements()) { statement->Visit(&varCount); }
      mainVars_ = varCount.LocalVars(); //we find out how many local vars we need
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        nullptr,
        make_unique<Instruction>(Instruction::kProgramStart), //this is so we know how many local vars to alocate on the stack
        nullptr,
        make_unique<Constant>(mainVars_));
      AddToEnd(std::move(newhead));
      for (auto& statement : program.statements()) { statement->Visit(this); }
      program.arithmetic_exp().Visit(this); //evaluate ae
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_ - 1),
        make_unique<Instruction>(Instruction::kReturn),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        nullptr,
        make_unique<Instruction>(Instruction::kProgramEnd),
        make_unique<Constant>(mainVars_),
        nullptr);
      AddToEnd(std::move(newhead));
      localVariables_.clear();
    }
    void IrGenVisitor::VisitFunctionCall(const FunctionCall& call) {
      int numArgs = call.arguments().size();
      for (int i = call.arguments().size() - 1; i >= 0; i--) {
        call.arguments()[i]->Visit(this);
        std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
          make_unique<Label>(labelNum_++),
          make_unique<Register>(register_number_ - 1),
          make_unique<Instruction>(Instruction::kArgument),
          nullptr,
          nullptr);
        AddToEnd(std::move(newhead));
      }
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Variable>(call.callee_name()),
        make_unique<Instruction>(Instruction::kCall),
        make_unique<Variable>(call.lhs().name()),
        make_unique<Constant>(numArgs));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitFunctionDef(const FunctionDef& def) {
      VarCountVisitor varsCounter;// we count number of params and local vars
      varsCounter.ScanningParams(true); // count params first we dont want to redeclare var if its in params already
      for (auto& param : def.parameters()) { param->Visit(&varsCounter); }
      varsCounter.ScanningParams(false);
      for (auto& statement : def.function_body()) { statement->Visit(&varsCounter); }
      int numLocalVar = varsCounter.LocalVars();
      std::shared_ptr<StatementNode>newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Variable>(def.function_name()),
        make_unique<Instruction>(Instruction::kFuncBegin), //call to crate func
        nullptr,
        make_unique<Constant>(numLocalVar));
      AddToEnd(std::move(newhead));
      readingParams_ = true;
      for (auto& param : def.parameters()) { param->Visit(this); }
      readingParams_ = false;
      for (auto& statement : def.function_body()) { statement->Visit(this); }
      def.retval().Visit(this);
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Register>(register_number_ - 1),
        make_unique<Instruction>(Instruction::kReturn),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Variable>(def.function_name()),
        make_unique<Instruction>(Instruction::kFuncEnd),
        nullptr,
        make_unique<Constant>(numLocalVar));
      AddToEnd(std::move(newhead));
      localVariables_.clear();
      paramVariables_.clear();
    }
    void IrGenVisitor::VisitLessThanExpr(const LessThanExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kLessThan),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kLessThanEqualTo),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitGreaterThanExpr(const GreaterThanExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGreaterThan),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGreaterThanEqualTo),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitEqualToExpr(const EqualToExpr& exp) {
      exp.lhs().Visit(this);
      exp.rhs().Visit(this);
      std::unique_ptr<Operand> op2 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::unique_ptr<Operand> op1 = std::move(ir_stack_.back());
      ir_stack_.pop_back();
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kEqualTo),
        std::move(op1),
        std::move(op2));
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitLogicalAndExpr(const LogicalAndExpr& exp) {
      IrGenVisitor countVisitor;
      exp.rhs().Visit(&countVisitor);
      int numRhs = countVisitor.NumberOfStatements();
      exp.lhs().Visit(this);
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + numRhs + 1),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      exp.rhs().Visit(this);
    }
    void IrGenVisitor::VisitLogicalOrExpr(const LogicalOrExpr& exp) {
      IrGenVisitor countVisitor;
      exp.rhs().Visit(&countVisitor);
      int numRhs = countVisitor.NumberOfStatements();
      exp.lhs().Visit(this);
      (*(--nodes.end()))->GetTarget().SetValue((*(--nodes.end()))->GetTarget().GetValue() + numRhs);
      exp.rhs().Visit(this);
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::VisitLogicalNotExpr(const LogicalNotExpr& exp) {
      exp.operand().Visit(this);
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
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
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(trueStatements + labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      for (auto& statement : conditional.true_branch()) {
        statement->Visit(this);
      }
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(falseStatements + labelNum_ + 1),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
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
      std::shared_ptr<StatementNode> newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(bodyStatements + labelNum_ + 2),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
      for (auto& statement : loop.body()) {
        statement->Visit(this);
      }
      newhead = std::make_shared< StatementNode>(
        make_unique<Label>(labelNum_++),
        make_unique<Constant>(startLabelNum),
        make_unique<Instruction>(Instruction::kGoto),
        nullptr,
        nullptr);
      AddToEnd(std::move(newhead));
    }
    void IrGenVisitor::AddToEnd(std::shared_ptr<StatementNode> newtail) {
      nodes.push_back(newtail);
    }
    void IrGenVisitor::PrintIR() {
      std::cout << "#### Start of IR ####" << endl;
      for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->Print();
        std::cout << endl;
      }
      std::cout << "#### END of IR ####" << endl;
    }
    int IrGenVisitor::NumberOfStatements() {
      return nodes.size();
    }
  } //namespace backend
} //namespace cs160
