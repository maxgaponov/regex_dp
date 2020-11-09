#include <gtest/gtest.h>
#include <dynamic_manip.h>

const char x = 'a';
const char nx = 'b';
const int k = 2;

TEST(test_dynamic_manip, sum) {
    DynamicState lhs(x, k);
    for (int i = 0; i <= k; ++i) {
        lhs.update_min_word_len(i, i);
    }
    DynamicState rhs(x, k);
    for (int i = 0; i <= k; ++i) {
        rhs.update_min_word_len(i, i * i);
    }
    DynamicState result = sum(lhs, rhs);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(result.get_min_word_len(i), i);
    }
}

TEST(test_dynamic_manip, concat) {
    DynamicState lhs(x, k);
    for (int i = 0; i < k; ++i) {
        lhs.update_min_word_len(i, 2);
    }
    DynamicState rhs(x, k);
    rhs.update_xword_in_l(2);
    for (int i = 0; i <= k; ++i) {
        rhs.update_min_word_len(i, 2);
    }
    DynamicState result = concat(lhs, rhs);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(result.get_min_word_len(i), 4);
        EXPECT_EQ(result.is_xword_in_l(i), false);
    }
}

TEST(test_dynamic_manip, iteration) {
    DynamicState ds(x, k);
    for (int i = 0; i < k; ++i) {
        ds.update_min_word_len(i, 2);
    }
    DynamicState result = iteration(ds);
    EXPECT_EQ(result.get_min_word_len(0), 0);
    EXPECT_EQ(result.get_min_word_len(1), 2);
    EXPECT_EQ(result.get_min_word_len(k), DynamicState::INF);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(result.is_xword_in_l(i), i == 0);
    }
}
