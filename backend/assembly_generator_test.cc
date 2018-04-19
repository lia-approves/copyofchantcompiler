// Copyright msg for cpplint
#include "abstract_syntax/abstract_syntax.h"
#include "backend/IR.h"
#include "gtest/gtest.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::intermediate_representation::Instruction;

using cs160::make_unique;

TEST(Basics, InstrCreation) {
  // auto instr = make_unique<StatementNode>(
  //   make_unique<Register>(),
  //   make_unique<Instruction>(),
  //   make_unique<Operand>(),
  //   make_unique<Operand>(),
  //   NULL);

  auto add_instr = new Instruction;

  // Instruction::Opcode addop = Instruction::kAdd;
  // std::cout << typeid(add_instr->GetOpcode()).name();
  EXPECT_EQ(add_instr->GetOpcode(), Instruction::kAdd);
}

// TEST(IntegerTest, Interpret7) {
//   InterpretVisitor interpreter_;
//   auto number = make_unique<IntegerExpr>(7);
//   number->Visit(&interpreter_);
//
//   EXPECT_EQ(interpreter_.GetOutputInt(), 7);
// }
