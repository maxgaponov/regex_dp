#include <dynamic.h>

DynamicState::DynamicState(char x, int k)
: x_(x), k_(k), min_word_len_(k + 1, INF), xword_in_l_(k + 1, false) {}

DynamicState::DynamicState(char x, int k, char a)
: DynamicState(x, k) {
    update_min_word_len(0, 1);
    if (x == a) {
        update_min_word_len(1, 1);
        update_xword(1);
    }
}

void DynamicState::update_min_word_len(int count, size_t value) {
    if (min_word_len_[count] > value) {
        min_word_len_[count] = value;
    }
}

void DynamicState::update_xword(int len) {
    xword_in_l_[len] = true;
}

size_t DynamicState::get_min_word_len(int count) const {
    return min_word_len_[count];
}

bool DynamicState::is_xword_in_l(int len) const {
    return xword_in_l_[len];
}

char DynamicState::get_x() const {
    return x_;
}

int DynamicState::get_k() const {
    return k_;
}
