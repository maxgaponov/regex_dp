#include <dynamic.h>

DynamicState::DynamicState(char x, int k)
: x_(x), k_(k), min_word_len_(k + 1, INF), xword_in_l_(k + 1, false) {}

DynamicState::DynamicState(char x, int k, char a)
: DynamicState(x, k) {
    update_min_word_len_(0, 1);
    if (x == a) {
        update_min_word_len_(1, 1);
        update_xword_(1);
    }
}

void DynamicState::update_min_word_len_(int len, size_t value) {
    if (min_word_len_[len] > value) {
        min_word_len_[len] = value;
    }
}

void DynamicState::update_xword_(int len) {
    xword_in_l_[len] = true;
}
