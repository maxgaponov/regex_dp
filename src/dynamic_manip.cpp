#include <dynamic_manip.h>
#include <algorithm>
#include <queue>

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
            if (rhs.is_xword_in_l(j) && i + j <= k) {
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

DynamicState iteration(const DynamicState& ds) {
    char x = ds.get_x();
    int k = ds.get_k();
    DynamicState result(x, k);
    result.update_xword_in_l(0);
    std::queue<int> q;
    for (int i = 0; i <= k; ++i) {
        if (ds.is_xword_in_l(i)) {
            result.update_xword_in_l(i);
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cnt = q.front();
        q.pop();
        for (int i = 0; i + cnt <= k; ++i) {
            if (result.is_xword_in_l(i) && !result.is_xword_in_l(i + cnt)) {
                result.update_xword_in_l(i + cnt);
                q.push(i + cnt);
            }
        }
    }
    for (int i = 0; i <= k; ++i) {
        if (result.is_xword_in_l(i)) {
            result.update_min_word_len(i, i);
        }
        result.update_min_word_len(i, ds.get_min_word_len(i));
    }
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (result.is_xword_in_l(j)) {
                size_t min_word_len = ds.get_min_word_len(i) + j;
                result.update_min_word_len(j, min_word_len);
            }
        }
    }
    int value = result.get_min_word_len(k);
    for (int i = k - 1; i >= 0; --i) {
        if (value > result.get_min_word_len(i)) {
            value = result.get_min_word_len(i);
        } else {
            result.update_min_word_len(i, value);
        }
    }
    return result;
}
