#include <gtest/gtest.h>
#include <solver.h>

TEST(test_solver, simple) {
    EXPECT_EQ(solve("a", 'a', 1), 1);
    EXPECT_EQ(solve("bb.", 'b', 1), 2);
    EXPECT_EQ(solve("ab.", 'b', 1), 2);
    EXPECT_EQ(solve("aaa..", 'a', 2), 3);
    EXPECT_EQ(solve("abb..", 'b', 2), 3);
    EXPECT_EQ(solve("c*", 'c', 1), 1);
    EXPECT_EQ(solve("c*", 'c', 2), 2);
    EXPECT_EQ(solve("ab+", 'a', 1), 1);
    EXPECT_EQ(solve("ab+", 'b', 1), 1);
    EXPECT_EQ(solve("aba.+", 'a', 1), 1);
}

TEST(test_solver, complex) {
    EXPECT_THROW(solve("ab+c.aba.*.bac.+.+*a.", 'b', 2), std::domain_error);
    EXPECT_EQ(solve("acb..bab.c.*.ab.ba.+.+*a.", 'a', 2), 4);
}
