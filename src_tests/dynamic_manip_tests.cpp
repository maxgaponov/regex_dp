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
