// Copyright (c) 2018, Team-Chant
#ifndef ABSTRACT_SYNTAX_PRINT_VISITOR_V5_H_
#define ABSTRACT_SYNTAX_PRINT_VISITOR_V5_H_

#include <sstream>
#include <string>
#include <vector>
#include "abstract_syntax/abstract_syntax_tree_v5.h"

namespace cs160 {
namespace abstract_syntax {
namespace version_5 {

class PrintVisitor : public AstVisitor {
 public:
  PrintVisitor() {}
  ~PrintVisitor() {}

  const std::string GetOutput() const { return output_.str(); }

  void VisitIntegerExpr(const IntegerExpr& exp) override {
    output_ << exp.value();
  }

  void VisitVariableExpr(const VariableExpr& exp) override {
    output_ << exp.name();
  }

  void VisitDereference(const Dereference& exp) override {
    exp.lhs().Visit(this);
    output_ << "->";
    exp.rhs().Visit(this);
  }

  void VisitAddExpr(const AddExpr& exp) override {
    output_ << "(+ ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitSubtractExpr(const SubtractExpr& exp) override {
    output_ << "(- ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitMultiplyExpr(const MultiplyExpr& exp) override {
    output_ << "(* ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitDivideExpr(const DivideExpr& exp) override {
    output_ << "(/ ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitLessThanExpr(const LessThanExpr& exp) override {
    output_ << "(< ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitLessThanEqualToExpr(const LessThanEqualToExpr& exp) override {
    output_ << "(<= ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitGreaterThanExpr(const GreaterThanExpr& exp) override {
    output_ << "(> ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitGreaterThanEqualToExpr(const GreaterThanEqualToExpr& exp) override {
    output_ << "(>= ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitEqualToExpr(const EqualToExpr& exp) override {
    output_ << "(= ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitLogicalAndExpr(const LogicalAndExpr& exp) override {
    output_ << "(&& ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitLogicalOrExpr(const LogicalOrExpr& exp) override {
    output_ << "(|| ";
    exp.lhs().Visit(this);
    output_ << " ";
    exp.rhs().Visit(this);
    output_ << ")";
  }

  void VisitLogicalNotExpr(const LogicalNotExpr& exp) override {
    output_ << "!";
    exp.operand().Visit(this);
  }

  void VisitAssignmentFromArithExp(const AssignmentFromArithExp& assignment) override {
    output_ << "(:= ";
    assignment.lhs().Visit(this);
    output_ << " ";
    assignment.rhs().Visit(this);
    output_ << ")";
  }

  void VisitAssignmentFromNewTuple(const AssignmentFromNewTuple& assignment) override {
    output_ << "(:= ";
    assignment.lhs().Visit(this);
    output_ << " ";
    assignment.rhs().Visit(this);
    output_ << ")";
  }

  void VisitStatementBlock(const std::vector<std::unique_ptr<const Statement>>& block) {
    for (int i = 0; i < block.size(); i++) {
      auto s = std::move(&block.at(i));
      (*s)->Visit(this);
      output_ << ";";
    }
  }

  void VisitConditional(const Conditional& conditional) override {
    output_ << "if(";
    conditional.guard().Visit(this);
    output_ << "){";
    VisitStatementBlock(conditional.true_branch());
    output_ << "}else{";
    VisitStatementBlock(conditional.false_branch());
    output_ << "}";
  }

  void VisitLoop(const Loop& loop) override {
    output_ << "while(";
    loop.guard().Visit(this);
    output_ << "){";
    VisitStatementBlock(loop.body());
    output_ << "}";
  }

  void VisitFunctionCall(const FunctionCall& call) override {
    call.lhs().Visit(this);
    output_ << ":=";
    output_ << call.callee_name();
    output_ << "(";
    const std::vector<std::unique_ptr<const ArithmeticExpr>>& arguments =
      std::move(call.arguments());
    for (int i = 0; i < arguments.size(); i++){
      auto a = std::move(&arguments.at(i));
      (*a)->Visit(this);
    }
    output_ << ")";
  }

  void VisitFunctionDef(const FunctionDef& def) override {
    output_ << "def ";
    output_ << def.function_name();
    output_ << "(";
    const std::vector<std::unique_ptr<const VariableExpr>>& parameters =
      std::move(def.parameters());
    for (int i = 0; i < parameters.size(); i++){
      auto a = std::move(&parameters.at(i));
      (*a)->Visit(this);
      output_ << ",";
    }
    output_ << "){";
    VisitStatementBlock(def.function_body());
    output_ << "return ";
    def.retval().Visit(this);
    output_ << "}";
  }

  void VisitProgram(const Program& program) override {
    /*
    const std::vector<std::unique_ptr<const Assignment>>& assignments =
      std::move(program.assignments());
    for (int i = 0; i < assignments.size(); i++) {
      auto p = std::move(&assignments.at(i));
      (*p)->Visit(this);
    }
    program.arithmetic_exp().Visit(this);
    */

    const std::vector<std::unique_ptr<const FunctionDef>>& defs =
      std::move(program.function_defs());
    for (int i = 0; i < defs.size(); i++){
      auto d = std::move(&defs.at(i));
      (*d)->Visit(this);
    }
    output_ << "main(){";
    VisitStatementBlock(program.statements());
    output_ << "return ";
    program.arithmetic_exp().Visit(this);
    output_ << "}";
  }

 private:
  std::stringstream output_;
};

}  // namespace version_5
}  // namespace abstract_syntax
}  // namespace cs160

#endif  // ABSTRACT_SYNTAX_PRINT_VISITOR_V5_H_
