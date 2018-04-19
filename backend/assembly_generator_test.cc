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
using cs160::intermediate_representation::Operand;
using cs160::intermediate_representation::Register;
using cs160::intermediate_representation::StatementNode;

using cs160::make_unique;

TEST(Basics, CreateInstruction) {
  // auto instr = make_unique<StatementNode>(
  //   make_unique<Register>(),
  //   make_unique<Instruction>(),
  //   make_unique<Operand>(),
  //   make_unique<Operand>(),
  //   NULL);

  auto add_instr = make_unique<Instruction>(Instruction::kAdd);

  // Instruction::Opcode addop = Instruction::kAdd;
  // std::cout << typeid(add_instr->GetOpcode()).name();
  EXPECT_EQ(add_instr->GetOpcode(), Instruction::kAdd);
}

TEST(Basics, CreateOperand) {
  auto operand = make_unique<Operand>(3);
  EXPECT_EQ(operand->GetValue(), 3);
}

TEST(Basics, CreateRegister) {
  auto reg = make_unique<Register>(5);
  EXPECT_EQ(reg->GetValue(), 5);
}

// Working on this one
TEST(Basics, CreateStatementNode) {
  auto add_instr = make_unique<Instruction>(Instruction::kAdd);
  auto op1 = make_unique<Operand>(3);
  auto op2 = make_unique<Operand>(4);
  auto reg = make_unique<Register>(5);
  auto next = make_unique<StatementNode>();
  auto statement = make_unique<StatementNode>(reg);

  EXPECT_EQ(2, 2);
}
// TEST(IntegerTest, Interpret7) {
//   InterpretVisitor interpreter_;
//   auto number = make_unique<IntegerExpr>(7);
//   number->Visit(&interpreter_);
//
//   EXPECT_EQ(interpreter_.GetOutputInt(), 7);
// }
