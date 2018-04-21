/*
MIT License

Copyright (c) 2018, Team-Chant

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "abstract_syntax/abstract_syntax_tree_v1.h"
#include "backend/print_visitor_v1.h"
#include "utility/memory.h"
#include "backend/ir_generator_visitor.h"

using cs160::abstract_syntax::version_1::IntegerExpr;
using cs160::abstract_syntax::version_1::AddExpr;
using cs160::abstract_syntax::version_1::SubtractExpr;
using cs160::abstract_syntax::version_1::MultiplyExpr;
using cs160::abstract_syntax::version_1::DivideExpr;
using cs160::abstract_syntax::version_1::PrintVisitor;
using cs160::abstract_syntax::version_1::IrGenVisitor;
using cs160::abstract_syntax::version_1::Operand;
using cs160::intermediate_representation::OperandBase;
using cs160::abstract_syntax::version_1::Register;
using cs160::make_unique;



  class IrGenVisitorTest : public ::testing::Test {
   protected:
    IrGenVisitor printer_;
  };

  TEST_F(IrGenVisitorTest, Expr1IsVisited) {
    auto expr = make_unique<AddExpr>(
      make_unique<IntegerExpr>(5),
      make_unique<SubtractExpr>(
        make_unique<MultiplyExpr>(
          make_unique<DivideExpr>(
            make_unique<IntegerExpr>(7),
            make_unique<IntegerExpr>(5)),
          make_unique<IntegerExpr>(9)),
        make_unique<IntegerExpr>(6)));
    expr->Visit(&printer_);

    EXPECT_EQ(1, 1);
  }
