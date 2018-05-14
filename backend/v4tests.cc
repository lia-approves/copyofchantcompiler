// Copyright msg for cpplint
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include "abstract_syntax/abstract_syntax.h"
#include "backend/ir_v4.h"
#include "gtest/gtest.h"
#include "utility/memory.h"
#include "backend/asm_generator_v4.h"
#include "backend/lowerer_v4.h"


using cs160::abstract_syntax::version_4::AstVisitor;
using cs160::abstract_syntax::version_4::ArithmeticExpr;
using cs160::abstract_syntax::version_4::AddExpr;
using cs160::abstract_syntax::version_4::SubtractExpr;
using cs160::abstract_syntax::version_4::MultiplyExpr;
using cs160::abstract_syntax::version_4::DivideExpr;
using cs160::abstract_syntax::version_4::IntegerExpr;
using cs160::abstract_syntax::version_4::VariableExpr;
using cs160::abstract_syntax::version_4::LessThanExpr;
using cs160::abstract_syntax::version_4::LessThanEqualToExpr;
using cs160::abstract_syntax::version_4::GreaterThanExpr;
using cs160::abstract_syntax::version_4::GreaterThanEqualToExpr;
using cs160::abstract_syntax::version_4::EqualToExpr;
using cs160::abstract_syntax::version_4::LogicalAndExpr;
using cs160::abstract_syntax::version_4::LogicalOrExpr;
using cs160::abstract_syntax::version_4::LogicalNotExpr;
using cs160::abstract_syntax::version_4::Statement;
using cs160::abstract_syntax::version_4::Assignment;
using cs160::abstract_syntax::version_4::Conditional;
using cs160::abstract_syntax::version_4::Loop;
using cs160::abstract_syntax::version_4::FunctionCall;
using cs160::abstract_syntax::version_4::FunctionDef;
using cs160::abstract_syntax::version_4::Program;

using cs160::backend::Operand;
using cs160::backend::Register;
using cs160::backend::StatementNode;
using cs160::backend::AsmProgram;
using cs160::backend::IrGenVisitor;
using cs160::backend::Text;
using cs160::backend::Label;
using cs160::backend::Constant;
using cs160::backend::Variable;


using cs160::make_unique;
using cs160::backend::AsmProgram;


TEST(Version4, IntegrationTest) {
  Statement::Block foo_statements;
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("a"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const AddExpr>(
      make_unique<const VariableExpr>("bob"),
      make_unique<const IntegerExpr>(8)))));
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("h"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("j"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("mike"),
    make_unique<const IntegerExpr>(45))));
  foo_statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("ab"),
    make_unique<const IntegerExpr>(45))));


  auto foo_retval = make_unique<const AddExpr>(
    make_unique<const VariableExpr>("bob"),
    make_unique<const IntegerExpr>(5));
  auto foo_params = std::vector<std::unique_ptr<const VariableExpr>>();
  foo_params.push_back(std::move(make_unique<const VariableExpr>("bob")));
  foo_params.push_back(std::move(make_unique<const VariableExpr>("jim")));
  foo_params.push_back(std::move(make_unique<const VariableExpr>("mike")));

  auto foo_def = make_unique<const FunctionDef>(
    "foo", std::move(foo_params),
    std::move(foo_statements),
    std::move(foo_retval));

  FunctionDef::Block function_defs;
  function_defs.push_back(std::move(foo_def));
  auto arguments = std::vector<std::unique_ptr<const ArithmeticExpr>>();
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));
  arguments.push_back(std::move(make_unique<const IntegerExpr>(17)));

  Statement::Block statements;
  statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("y"),
    make_unique<const IntegerExpr>(9))));
  statements.push_back(std::move(make_unique<const Assignment>(
    make_unique<const VariableExpr>("x"),
    make_unique<const IntegerExpr>(1))));
  statements.push_back(std::move(make_unique<const FunctionCall>(
    make_unique<const VariableExpr>("foo_retval"),
    "foo",
    std::move(arguments))));

  auto ae = make_unique<const AddExpr>(
    make_unique<const IntegerExpr>(12),
    make_unique<const VariableExpr>("foo_retval"));

  auto ast = make_unique<const Program>(std::move(function_defs),
  std::move(statements), std::move(ae));

  IrGenVisitor irGen;
  ast->Visit(&irGen);
  AsmProgram testasm;
  testasm.IrToAsm(&irGen);

  std::ofstream test_output_file;
  test_output_file.open("testfile.s");
  test_output_file << testasm.GetASMString();
  system("gcc testfile.s && ./a.out > test_output.txt");

  std::ifstream output_file;
  output_file.open("test_output.txt");
  std::string output;
  output_file >> output;

  EXPECT_EQ("42", output);
}
