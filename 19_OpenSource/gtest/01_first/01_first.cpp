
#include "gtest/gtest.h"

using ::testing::Test;

TEST(SkipTest, DoesSkip) {
  GTEST_SKIP();
  EXPECT_EQ(0, 1);
}

class Fixture : public Test {
 protected:
  void SetUp() override {
    GTEST_SKIP() << "skipping all tests for this fixture";
  }
};

TEST_F(Fixture, SkipsOneTest) {
  EXPECT_EQ(5, 7);
}

TEST_F(Fixture, SkipsAnotherTest) {
  EXPECT_EQ(99, 100);
}