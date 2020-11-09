#include <gtest/gtest.h>
#include <dynamic.h>

const char x = 'a';
const char nx = 'b';
const int k = 4;

TEST(test_dynamic, construct_empty) {
    DynamicState empty(x, k);
    EXPECT_EQ(empty.get_k(), k);
    EXPECT_EQ(empty.get_x(), x);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(empty.get_min_word_len(i), DynamicState::INF);
        EXPECT_EQ(empty.is_xword_in_l(i), false);
    }
}

TEST(test_dynamic, construct_x) {
    DynamicState ds(x, k, x);
    EXPECT_EQ(ds.get_k(), k);
    EXPECT_EQ(ds.get_x(), x);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(ds.get_min_word_len(i), (i <= 1 ? 1 : DynamicState::INF));
        EXPECT_EQ(ds.is_xword_in_l(i), (i == 1));
    }
}

TEST(test_dynamic, construct_nx) {
    DynamicState ds(x, k, nx);
    EXPECT_EQ(ds.get_k(), k);
    EXPECT_EQ(ds.get_x(), x);
    for (int i = 0; i <= k; ++i) {
        EXPECT_EQ(ds.get_min_word_len(i), (i == 0 ? 1 : DynamicState::INF));
        EXPECT_EQ(ds.is_xword_in_l(i), false);
    }
}

TEST(test_dynamic, update_min_word_len) {
    DynamicState ds(x, k);
    ds.update_min_word_len(0, 5);
    ds.update_min_word_len(1, 7);
    EXPECT_EQ(ds.get_min_word_len(0), 5);
    EXPECT_EQ(ds.get_min_word_len(1), 7);
    for (int i = 2; i <= k; ++i) {
        EXPECT_EQ(ds.get_min_word_len(i), (i == 0 ? 1 : DynamicState::INF));
    }
}

TEST(test_dynamic, update_xword_in_l) {
    DynamicState ds(x, k);
    ds.update_xword_in_l(0);
    ds.update_xword_in_l(k);
    EXPECT_EQ(ds.is_xword_in_l(0), true);
    EXPECT_EQ(ds.is_xword_in_l(k), true);
    for (int i = 1; i < k; ++i) {
        EXPECT_EQ(ds.is_xword_in_l(i), false);
    }
}
