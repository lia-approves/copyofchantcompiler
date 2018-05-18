// Copyright(c) 2018, Team Chant


#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "backend/ir_v5.h"
#include "utility/memory.h"
#include "abstract_syntax/abstract_syntax_tree_v5.h"
#include "backend/lowerer_v5.h"

namespace cs160 {
namespace backend {

void CountVisitor::VisitIntegerExpr(const IntegerExpr& exp) {  }

void CountVisitor::VisitDereference(const Dereference& exp) {
  //!!
}

void CountVisitor::VisitVariableExpr(const VariableExpr& exp) {
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(),
      (exp.name())) != paramVariables_.end();
    if (foundinParams) {
    } else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (exp.name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(exp.name()); }
      } else if (scanningParams_ == true) {
        bool found = std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          (exp.name())) != paramVariables_.end();
        if (!found) { paramVariables_.push_back(exp.name()); }
      }
    }
  }

void CountVisitor::VisitAddExpr(const AddExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitSubtractExpr(const SubtractExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitMultiplyExpr(const MultiplyExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitDivideExpr(const DivideExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitLessThanExpr(const LessThanExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitGreaterThanExpr(const GreaterThanExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitGreaterThanEqualToExpr(
  const GreaterThanEqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitEqualToExpr(const EqualToExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitLogicalAndExpr(const LogicalAndExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitLogicalOrExpr(const LogicalOrExpr& exp) {
    exp.lhs().Visit(this);
    exp.rhs().Visit(this);
  }

void CountVisitor::VisitLogicalNotExpr(const LogicalNotExpr& exp) {
    exp.operand().Visit(this);
  }

void CountVisitor::VisitAssignmentFromArithExp(const AssignmentFromArithExp& assignment) {
  /*  assignment.rhs().Visit(this);
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(),
      (assignment.lhs().name())) != paramVariables_.end();
    if (foundinParams) {
    } else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (assignment.lhs().name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(assignment.lhs().name()); }
      } else if (scanningParams_ == true) {
        bool found = std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          (assignment.lhs().name())) != paramVariables_.end();
        if (!found) { paramVariables_.push_back(assignment.lhs().name()); }
      }
    }*/
    numMainVars_++;
  }

void CountVisitor::VisitConditional(const Conditional& conditional) {
    conditional.guard().Visit(this);
    for (auto& statement : conditional.true_branch()) {
      statement->Visit(this);
    }
    for (auto& statement : conditional.false_branch()) {
      statement->Visit(this);
    }
  }

void CountVisitor::VisitAssignmentFromNewTuple(
    const AssignmentFromNewTuple& assignment) {
  assignment.lhs().Visit(this);
  assignment.rhs().Visit(this);
  // count_++;
}
void CountVisitor::VisitLoop(const Loop& loop) {
    loop.guard().Visit(this);
    for (auto& statement : loop.body()) {
      statement->Visit(this);
    }
  }

void CountVisitor::VisitProgram(const Program& program) {
    for (auto& statement : program.statements()) {
      statement->Visit(this);
    }
    program.arithmetic_exp().Visit(this);
  }
void CountVisitor::VisitFunctionCall(const FunctionCall& call) {
    bool foundinParams = std::find(
      paramVariables_.begin(),
      paramVariables_.end(), (call.lhs().name())) != paramVariables_.end();
    if (foundinParams) {
    }  else {
      if (scanningParams_ == false) {
        bool found = std::find(
          localVariables_.begin(),
          localVariables_.end(),
          (call.lhs().name())) != localVariables_.end();
        if (!found) { localVariables_.push_back(call.lhs().name()); }
      } else if (scanningParams_ == true) {
        bool found = std::find(
          paramVariables_.begin(),
          paramVariables_.end(),
          (call.lhs().name())) != paramVariables_.end();
        if (!found) { paramVariables_.push_back(call.lhs().name()); }
      }
    }
  }

void CountVisitor::VisitFunctionDef(const FunctionDef& def) { }

void CountVisitor::ScanningParams(bool scanningParams) {
  scanningParams_ = scanningParams;
}



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
void IrGenVisitor::VisitIntegerExpr(const IntegerExpr& exp) {
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




void IrGenVisitor::VisitDereference(const Dereference& exp) {
  exp.lhs().Visit(this);
  Operand* op1 = stack_.back();
  stack_.pop_back();
}



void IrGenVisitor::VisitVariableExpr(const VariableExpr& exp) {
  stack_.push_back(new Variable(exp.name()));
  int pos;
  int stackOffset;
  bool foundinParams = std::find(
    paramVariables_.begin(),
    paramVariables_.end(),
    (exp.name())) != paramVariables_.end();

  if (foundinParams) {
    // This variable is a parameter
    pos = std::distance(paramVariables_.begin(), std::find(
      paramVariables_.begin(), paramVariables_.end(), exp.name()));
    stackOffset = 1 * ((pos + 2) * 8);
    stack_.back()->SetStackOffset(stackOffset);
  } else {
    // This variable is not a parameter
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
      // Add variable to parameters vector
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
    // TODO(Taylor): move string logic to asm generator
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
void IrGenVisitor::VisitAssignmentFromArithExp(const AssignmentFromArithExp& assignment) {
  assignment.lhs().Visit(this);
  Operand* op1 = stack_.back();
  stack_.pop_back();

  // pop %rax;
  // pop %rbx;
  // mult $8, %rbx;
  // add %rbx, %rax;
  // push %rax;
  // $2(%rsp)
  // int pos;
  // int stackOffset = 8;
  assignment.rhs().Visit(this);
  Operand* op2 = stack_.back();
  stack_.pop_back();
  StatementNode *newtail = new StatementNode(
    new Label(labelNum_++),
    op1,
    new Operator(Operator::kAssign),
    nullptr,
    op2,
    nullptr);
  // newtail->GetTarget()->SetStackOffset(stackOffset);
  AddToEnd(newtail);
  stack_.push_back(new Register(register_number_));
}




void IrGenVisitor::VisitProgram(const Program& program) {
  for (auto& def : program.function_defs()) {
    def->Visit(this);
  }
  CountVisitor varCount;
  varCount.ScanningParams(false);
  for (auto& statement : program.statements()) {
    statement->Visit(&varCount);
  }
  // mainVars_ = varCount.LocalVars();
  mainVars_ = varCount.GetNumMainVars() + varCount.LocalVars();
  // TODO(Taylor) Check the logic of the above line of code. It may just be a hack.
  string main = ".global main\n.text\nmain:\nmov %rsp, %rbp\n";
  // main.append("mov $0x2d, %rax\nmov $0, %rbx\nsyscall\nmov %rax, %rcx\n");
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
void IrGenVisitor::VisitFunctionCall(const FunctionCall& call) {
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

void IrGenVisitor::VisitFunctionDef(const FunctionDef& def) {
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

void IrGenVisitor::VisitAssignmentFromNewTuple(
    const AssignmentFromNewTuple& assignment) {
  assignment.lhs().Visit(this);
  assignment.rhs().Visit(this);
  // count_++;
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
void IrGenVisitor::VisitGreaterThanEqualToExpr(
  const GreaterThanEqualToExpr& exp) {
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
  std::cout << "\n#### End of IR ####*/\n\n";
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


}  // namespace backend
}  // namespace cs160
