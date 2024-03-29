// Copyright (c) 2018, Team-Chant

#include <string>
#include "gtest/gtest.h"
#include "frontend/v5/frontend.h"
#include "abstract_syntax/print_visitor_v5.h"

namespace cs160 {
namespace frontend {
namespace Parse {

class FrontendTest : public ::testing::Test {
 protected:
  bool test = false;
  abstract_syntax::version_5::PrintVisitor printer_;
};

// TEST_F(FrontendTest, IntegerTest1) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
// TEST_F(FrontendTest, IntegerTest2) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1234");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1234");
// }
//
// TEST_F(FrontendTest, IntegerTest3) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("4321");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "4321");
// }

// TEST_F(FrontendTest, VariableTest1) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("a");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "a");
// }
//
// TEST_F(FrontendTest, VariableTest2) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd");
// }
//
// TEST_F(FrontendTest, VariableTest3) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd123");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd123");
// }
//
// TEST_F(FrontendTest, VariableTest4) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("abcd_123");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "abcd_123");
// }

//
// TEST_F(FrontendTest, BasicUnaryTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
// TEST_F(FrontendTest, BasicUnary2Test) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("-1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 0 1)");
// }
//
// TEST_F(FrontendTest, NegativeUnaryTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("---1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 0 1)");
// }
//
//
// TEST_F(FrontendTest, PositiveUnaryTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("----1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
// TEST_F(FrontendTest, VariableUnaryTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("-a");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 0 a)");
// }
//
//
// TEST_F(FrontendTest, BasicAdditionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1+2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 2)");
// }
//
// TEST_F(FrontendTest, BasicSubtractionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1-2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 1 2)");
// }
//
// TEST_F(FrontendTest, HardAdditionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1+2+3+4+5");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 1 (+ 2 (+ 3 (+ 4 5))))");
// }
//
// TEST_F(FrontendTest, HardSubtractionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1-2-3-4-5");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(- 1 (- 2 (- 3 (- 4 5))))");
// }
//
// TEST_F(FrontendTest, MultAdditionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("5*4+6*7");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ (* 5 4) (* 6 7))");
// }
//
// TEST_F(FrontendTest, DivAdditionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("5/4+6-7/8");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ (/ 5 4) (- 6 (/ 7 8)))");
// }
//
// TEST_F(FrontendTest, BasicMultiplicationTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1*2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 2)");
// }
//
// TEST_F(FrontendTest, BasicDivisionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("2/1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(/ 2 1)");
// }
//
// TEST_F(FrontendTest, TripleMultiplicationTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1*2*3");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 (* 2 3))");
// }
//
// TEST_F(FrontendTest, TripleDivideTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1/2/3");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(/ 1 (/ 2 3))");
// }
//
// TEST_F(FrontendTest, MultDivCombinedTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("1*2/3*5");
//   std::cout << "done with stringToAST" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(* 1 (/ 2 (* 3 5)))");
// }
//
// TEST_F(FrontendTest, AdvancedAdditionTest) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("2+2+3+4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 2 (+ 2 (+ 3 4)))");
// }
//
// TEST_F(FrontendTest, AdvancedEquation1Test) {
//   // make a basic expression and parse
//   auto ret = Frontend::stringToAst("2+3-4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(+ 2 (- 3 4))");
// }

// TEST_F(FrontendTest, PrimaryTest1) {
//     auto ret = Frontend::stringToAst("(1*2)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "(* 1 2)");
// }
//
// TEST_F(FrontendTest, PrimaryTest2) {
//     auto ret = Frontend::stringToAst("1");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "1");
// }
//
// TEST_F(FrontendTest, PrimaryTest3) {
//     auto ret = Frontend::stringToAst("abc");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "abc");
// }

// TEST_F(FrontendTest, DrefTest1) {
//     auto ret = Frontend::stringToAst("abc->12");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "abc->12");
// }
//
// TEST_F(FrontendTest, DrefTest2) {
//     auto ret = Frontend::stringToAst("abc->(1*2)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "abc->(* 1 2)");
// }
//
// TEST_F(FrontendTest, DrefTest3) {
//     auto ret = Frontend::stringToAst("abc_123->(1*2+4*3)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "abc_123->(+ (* 1 2) (* 4 3))");
// }

// TEST_F(FrontendTest, RopTestGeq) {
//     auto ret = Frontend::stringToAst(">=");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), ">=");
// }
//
// TEST_F(FrontendTest, RopTestLeq) {
//     auto ret = Frontend::stringToAst("<=");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "<=");
// }
//
// TEST_F(FrontendTest, RopTestEq) {
//     auto ret = Frontend::stringToAst("=");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "=");
// }
//
// TEST_F(FrontendTest, RopTestLess) {
//     auto ret = Frontend::stringToAst(">");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), ">");
// }
//
// TEST_F(FrontendTest, RopTestGreater) {
//     auto ret = Frontend::stringToAst("<");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "<");
// }
//
// TEST_F(FrontendTest, ReTest1) {
//     auto ret = Frontend::stringToAst("(1+2)>(3+4)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "(> (+ 1 2) (+ 3 4))");
// }
//
// TEST_F(FrontendTest, ReTest2) {
//     auto ret = Frontend::stringToAst("!(1+2)>(3+4)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "!(> (+ 1 2) (+ 3 4))");
// }
// TEST_F(FrontendTest, ReTest3) {
//     auto ret = Frontend::stringToAst("(1+2)&&(1+2)<(3+4)");
//     ret->Visit(&printer_);
//     ASSERT_EQ(printer_.GetOutput(), "(&& (+ 1 2) (< (+ 1 2) (+ 3 4)))");
// }

// TEST_F(FrontendTest, AssignTest1) {
//   auto ret = Frontend::stringToAst("a:=1");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(:= a 1)");
// }
//
// TEST_F(FrontendTest, AssignTest2) {
//   auto ret = Frontend::stringToAst("abc_123:=1*2");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(:= abc_123 (* 1 2))");
// }
//
//
// TEST_F(FrontendTest, AssignTest3) {
//   auto ret = Frontend::stringToAst("abc_123:=1*2+3*4");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "(:= abc_123 (+ (* 1 2) (* 3 4)))");
// }
//
// TEST_F(FrontendTest, CallTest1) {
//   auto ret = Frontend::stringToAst("a:=hello(4;5;6;)");
//   std::cout << "we got: " << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "a:=hello(456)");
// }
//
// TEST_F(FrontendTest, CallTest2) {
//   auto ret = Frontend::stringToAst("a:=hello(45;500;61;)");
//   std::cout << "we got: " << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "a:=hello(4550061)");
// }
//
// TEST_F(FrontendTest, BlockTest) {
//   auto ret = Frontend::stringToAst("{a:=4;b:=5;}");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "4");
// }

// TEST_F(FrontendTest, LoopTest1) {
//   auto ret = Frontend::stringToAst("while(4<5){a:=5;}");
//   std::cout << "in test" << std::endl;
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "while((< 4 5)){(:= a 5);}");
// }
//
// TEST_F(FrontendTest, LoopTest2) {
//   auto ret = Frontend::stringToAst("while(!5<4){a:=hello(5;);}");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "while(!(< 5 4)){a:=hello(5);}");
// }

// TEST_F(FrontendTest, CondTest1) {
//   auto ret = Frontend::stringToAst("if(5<4){while(!5<4){a:=hello(5;);};}else{a:=5;}");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "if((< 5 4)){while(!(< 5 4)){a:=hello(5);};}else{(:= a 5);}");
// }
//
// TEST_F(FrontendTest, CondTest2) {
//   auto ret = Frontend::stringToAst("if(!5<4){a:=hello(4;);}else{b:=6;}");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "if(!(< 5 4)){a:=hello(4);}else{(:= b 6);}");
// }


// TEST_F(FrontendTest, FunDefTest) {
//   auto ret = Frontend::stringToAst("def hello(a;b;){{if(5<4){while(!5<4){a:=hello(5;);};}else{a:=5;};}return 4*1}");
//   ret->Visit(&printer_);
//   ASSERT_EQ(printer_.GetOutput(), "def hello(a,b,){if((< 5 4)){while(!(< 5 4)){a:=hello(5);};}else{(:= a 5);};return (* 4 1)}");
// }


TEST_F(FrontendTest, ProgramTest1) {
  auto ret = Frontend::stringToAst(
    "def hello(a;b;){{if(5<4){while(!5<4){a:=hello(5;);};}else{a:=5;};}return 4*1}main(){{b:=4;}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"def hello(a,b,){if((< 5 4)){while(!(< 5 4)){a:=hello(5);};}else{(:= a 5);};return (* 4 1)}main(){(:= b 4);return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest2) {
  auto ret = Frontend::stringToAst(
    "main(){{if(5<4){if(1>=2){abc_123:=50;}else{a:=5;};}else{a:=5;};}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"main(){if((< 5 4)){if((>= 1 2)){(:= abc_123 50);}else{(:= a 5);};}else{(:= a 5);};return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest3) {
  auto ret = Frontend::stringToAst(
    "main(){{b:=4;}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"main(){(:= b 4);return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest4) {
  auto ret = Frontend::stringToAst(
    "def hello(a;b;){{if(5<4){while(!5<4){a:=hello(5;);};}else{a:=5;};}return 4*1}def goodbye(c;d;){{if(5<4){while(!5<4){a:=hello(5;);};}else{a:=5;};}return 4*1}main(){{b:=4;}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"def hello(a,b,){if((< 5 4)){while(!(< 5 4)){a:=hello(5);};}else{(:= a 5);};return (* 4 1)}def goodbye(c,d,){if((< 5 4)){while(!(< 5 4)){a:=hello(5);};}else{(:= a 5);};return (* 4 1)}main(){(:= b 4);return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest5) {
  auto ret = Frontend::stringToAst(
  "def goodbye(){{a:=20;b:=20;}return 5*1}main(){{c1:=goodbye();}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"def goodbye(){(:= a 20);(:= b 20);return (* 5 1)}main(){c1:=goodbye();return (+ 3 1)}");
}
TEST_F(FrontendTest, ProgramTest6) {
  auto ret = Frontend::stringToAst(
    "def goodbye(){{a:=20;if(3=2){a:=hello(5;);b:=12;}else{b_c:=43;};}return 5*1}main(){{c1:=goodbye();}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"def goodbye(){(:= a 20);if((= 3 2)){a:=hello(5);(:= b 12);}else{(:= b_c 43);};return (* 5 1)}main(){c1:=goodbye();return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest7) {
  auto ret = Frontend::stringToAst(
    "def goodbye(){{while(5=5){while(3>=4){a:=5;};};}return 5*1}main(){{c1:=goodbye();}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"def goodbye(){while((= 5 5)){while((>= 3 4)){(:= a 5);};};return (* 5 1)}main(){c1:=goodbye();return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest8) {
  auto ret = Frontend::stringToAst(
    "main(){{c1:=5*4+8/7+2*4;}return 3+1}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"main(){(:= c1 (+ (* 5 4) (+ (/ 8 7) (* 2 4))));return (+ 3 1)}");
}

TEST_F(FrontendTest, ProgramTest9) {
  auto ret = Frontend::stringToAst(
    "main(){{c1:=5*4+8/7+2*4;}return 5-8+9*3/5}");
  ret->Visit(&printer_);
  ASSERT_EQ(printer_.GetOutput(),
"main(){(:= c1 (+ (* 5 4) (+ (/ 8 7) (* 2 4))));return (- 5 (+ 8 (* 9 (/ 3 5))))}");
}

}  // namespace Parse
}  // namespace frontend
}  // namespace cs160
