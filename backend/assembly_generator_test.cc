// Copyright msg for cpplint
#include "abstract_syntax/abstract_syntax.h"
#include "backend/intermediate_representation_v1.h"
#include "gtest/gtest.h"
#include "utility/memory.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;

using cs160::backend::Instruction;
using cs160::backend::Operand;
using cs160::backend::Register;
using cs160::backend::StatementNode;

using cs160::make_unique;

TEST(Basics, CreateInstruction) {
  auto add_instr = make_unique<Instruction>(Instruction::kAdd);
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
/*TEST(Basics, CreateStatementNode) {
  auto statement = make_unique<StatementNode>(
    make_unique<Register>(5),
    make_unique<Instruction>(Instruction::kAdd),
    make_unique<Operand>(2),
    make_unique<Operand>(3),
    make_unique<StatementNode>());

  EXPECT_EQ(statement->GetTarget().GetValue(), 5);
  EXPECT_EQ(statement->GetInstruction().GetOpcode(), Instruction::kAdd);
  EXPECT_EQ(statement->GetOp1().GetValue(), 2);
  EXPECT_EQ(statement->GetOp2().GetValue(), 3);
}*/
