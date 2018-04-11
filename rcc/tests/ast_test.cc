
#include "gtest/gtest.h"
#include "rcc.h"

TEST(AST_Test, AST_Test_Addition) {
	EXPECT_EQ(rcc::AST_Test_Addition(), 0x12CC);
}

