#pragma once
#include <vector>

class DynamicState {
public:
    DynamicState(char x, int k);
    DynamicState(char x, int k, char a);
private:
    void update_min_word_len_(int len, size_t value);
    void update_xword_(int len);

    static const int INF = 1'000'000'000;
    char x_;
    int k_;
    std::vector<size_t> min_word_len_;
    std::vector<bool> xword_in_l_;
};
