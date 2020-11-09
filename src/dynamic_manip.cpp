#include <dynamic_manip.h>
#include <algorithm>

DynamicState sum(const DynamicState& lhs, const DynamicState& rhs) {
    char x = lhs.get_x();
    int k = lhs.get_k();
    DynamicState result(x, k);
    for (int i = 0; i <= k; ++i) {
        size_t min_word_len = std::min(lhs.get_min_word_len(i), rhs.get_min_word_len(i));
        result.update_min_word_len(i, min_word_len);
        if (lhs.is_xword_in_l(i) || rhs.is_xword_in_l(i)) {
            result.update_xword_in_l(i);
        }
    }
    return result;
}

DynamicState concat(const DynamicState& lhs, const DynamicState& rhs) {
    char x = lhs.get_x();
    int k = lhs.get_k();
    DynamicState result(x, k);
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k; ++j) {
            size_t min_word_len = lhs.get_min_word_len(i) + rhs.get_min_word_len(j);
            result.update_min_word_len(j, min_word_len);
            if (rhs.is_xword_in_l(j)) {
                min_word_len = lhs.get_min_word_len(i) + j;
                result.update_min_word_len(i + j, min_word_len);
            }
            if (lhs.is_xword_in_l(i) && rhs.is_xword_in_l(j) && i + j <= k) {
                result.update_xword_in_l(i + j);
            }
        }
    }
    return result;
}
