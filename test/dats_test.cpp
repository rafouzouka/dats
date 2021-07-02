#include <gtest/gtest.h>

extern "C"
{
    #include "../src/dats.h"
}

TEST(HelloTest, BasicAssertions) {
  
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");

  // Expect equality.
  EXPECT_EQ('c', 'c');
}

TEST(Hello, BasicAssertionss)
{
    
}